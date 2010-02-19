#include "textedit.h"

#include "barrenombres.h"
#include "coloration.h"
#include "gestionnaireparametres.h"
#include "window.h"

#include <QtGui/QApplication>
#include <QtGui/QDropEvent>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMimeSource>
#include <QtGui/QPainter>
#include <QtGui/QScrollBar>
#include <QtGui/QToolTip>

DropableTextEdit::DropableTextEdit(TextEdit *pParent) : QTextEdit(pParent), m_parent(pParent) {
    setAcceptDrops(true);
}

void DropableTextEdit::dropEvent(QDropEvent *pEvent) {
    const QMimeData *mimeData = pEvent->mimeData();
    if (mimeData->hasFormat("text/plain")) {
        m_parent->getParent()->ouvrirFichier(mimeData->text().trimmed().replace("file://", ""));
        pEvent->accept();
    }
}


TextEdit::TextEdit(Window *pParent) : QFrame(pParent), m_parent(pParent) {
    setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    setLineWidth(2);

    m_textEdit = new DropableTextEdit(this);
    m_textEdit->setFrameStyle(QFrame::NoFrame);
    m_color = new Coloration(m_textEdit->document());

    m_barreNombres = 0;

    connect(m_textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    highlightCurrentLine();

    loadSettings();
}

TextEdit::~TextEdit() {
    if (m_barreNombres != 0)
        delete m_barreNombres;
    delete m_color;
    delete m_textEdit;
}


void TextEdit::ajouterTexte(QString pTexte) {
    m_textEdit->insertPlainText(pTexte);
}


void TextEdit::changementLigne(int pNumLigne) {
    QTextBlock block;
    QTextCursor cursor;
    QTextBlockFormat blockFormat;

    block = getTextEdit()->document()->findBlockByLineNumber(pNumLigne - 1);
    cursor = QTextCursor(block);
    blockFormat = cursor.blockFormat();
    blockFormat.clearBackground();
    cursor.setBlockFormat(blockFormat);
    getTextEdit()->setTextCursor(cursor);
}

void TextEdit::recherche(QString pRecherche) {
    getTextEdit()->find(pRecherche);
}

void TextEdit::remplacement(QString pRecherche, QString pRemplacement) {
    if (getTextEdit()->find(pRecherche)) {
        getTextEdit()->textCursor().removeSelectedText();
        int pos = getTextEdit()->textCursor().position();
        getTextEdit()->insertPlainText(pRemplacement);
        int newPos = getTextEdit()->textCursor().position();
        QTextCursor tmp = getTextEdit()->textCursor();
        tmp.setPosition(pos, QTextCursor::MoveAnchor);
        tmp.setPosition(newPos, QTextCursor::KeepAnchor);
        getTextEdit()->setTextCursor(tmp);
    }
}

void TextEdit::remplacerTout(QString pRecherche, QString pRemplacement) {
    while (getTextEdit()->find(pRecherche, QTextDocument::FindBackward) || getTextEdit()->find(pRecherche))
        remplacement(pRecherche, pRemplacement);
}

void TextEdit::wheelEvent(QWheelEvent* pEvent) {
    if (qApp->keyboardModifiers() & Qt::ControlModifier) {
        if (pEvent->delta() > 0)
            getTextEdit()->zoomIn();
        else if (pEvent->delta() < 0)
            getTextEdit()->zoomOut();
        pEvent->accept();
    }
}


void TextEdit::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!getTextEdit()->isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        selection.format.setBackground(GestionnaireParametres::getInstance()->getCouleurLigneActuelle());
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = getTextEdit()->textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    getTextEdit()->setExtraSelections(extraSelections);
}


void TextEdit::changerCouleur() {
    m_color->deleteLater();
    m_color = new Coloration(getTextEdit()->document());
}

void TextEdit::loadSettings() {
    m_isLineNumberArea = GestionnaireParametres::getInstance()->getNumerotationLignes();
    m_isRetourLigne = GestionnaireParametres::getInstance()->getRetourLigne();
    m_tailleTab = GestionnaireParametres::getInstance()->getTailleTab();

    delete layout();
    QHBoxLayout *box = new QHBoxLayout(this);
    box->setSpacing(0);
    box->setMargin(0);
    if (m_isLineNumberArea) {
        m_barreNombres = new BarreNombres(this);
        m_barreNombres->setTextEdit(m_textEdit);
        box->addWidget(m_barreNombres);
    } else if (m_barreNombres != 0) {
        delete m_barreNombres;
        m_barreNombres = 0;
    }
    box->addWidget(m_textEdit);

    if (m_isRetourLigne)
        getTextEdit()->setLineWrapMode(QTextEdit::WidgetWidth);
    else
        getTextEdit()->setLineWrapMode(QTextEdit::NoWrap);
    changerCouleur();
    getTextEdit()->setTabStopWidth(fontMetrics().width(QLatin1Char(' ')) * m_tailleTab);
    highlightCurrentLine();
    update();
    repaint();
}
