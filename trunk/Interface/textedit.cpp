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
#include <QtGui/QTextDocument>
#include <QtGui/QToolTip>

#include <QtCore/QDebug>


/*! \brief Constructeur. Accepte le drag'n'drop.

  \param pParent Widget parent
*/
DropableTextEdit::DropableTextEdit(TextEdit *pParent) : QTextEdit(pParent), m_parent(pParent) {
    setAcceptDrops(true);
}


/*! \brief Méthode appelée automatiquement lors du drag'n'drop d'un fichier sur l'éditeur.

  Ouvre le fichier si il est possible de le faire.
  \param pEvent Évènement de drag'n'drop
*/
void DropableTextEdit::dropEvent(QDropEvent *pEvent) {
    const QMimeData *mimeData = pEvent->mimeData();
    if (mimeData->hasFormat("text/plain")) {
        m_parent->getParent()->ouvrirFichier(mimeData->text().trimmed().replace("file://", ""));
        pEvent->accept();
    }
}


/*! \brief Méthode appelée automatiquement lors de l'utilisation de la molette au dessus de l'éditeur.

  Zomme/dézomme si la touche ctrl est enfoncée, sinon monte/descend dans l'éditeur.
  \param pEvent Évènement de scroll
*/
void DropableTextEdit::wheelEvent(QWheelEvent* pEvent) {
    if (qApp->keyboardModifiers() & Qt::ControlModifier) {
        if (pEvent->delta() > 0)
            zoomIn();
        else if (pEvent->delta() < 0)
           zoomOut();
        pEvent->accept();
    } else
        QTextEdit::wheelEvent(pEvent);
}


/*! \brief Constructeur. Initialise un éditeur de texte et charge les préférences.

  \param pParent Widget parent
*/
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


/*! \brief Destruteur. Détruit la barre de numérotation de lignes si elle existe.
*/
TextEdit::~TextEdit() {
    if (m_barreNombres != 0)
        delete m_barreNombres;
    delete m_color;
    delete m_textEdit;
}


/*! \brief Ajoute du texte à l'éditeur.

  \param pTexte Texte à ajouter
*/
void TextEdit::ajouterTexte(QString pTexte) {
    m_textEdit->insertPlainText(pTexte);
}


/*! \brief Change la ligne actuelle de l'éditeur de texte.

  \param pNumLigne Numéro de la ligne où aller
*/
void TextEdit::changementLigne(int pNumLigne) {
    getTextEdit()->setTextCursor(QTextCursor(getTextEdit()->document()->findBlockByLineNumber(pNumLigne - 1)));
}


/*! \brief Recherche un texte dans l'éditeur.

  \param pRecherche Texte à rechercher
*/
void TextEdit::recherche(TRecherche pRecherche) {
    QTextDocument::FindFlags flags = 0;
    if (pRecherche.casse)
        flags |= QTextDocument::FindCaseSensitively;
    if (pRecherche.motEntier)
        flags |= QTextDocument::FindWholeWords;
    getTextEdit()->find(pRecherche.recherche, flags);
}


/*! \brief Remplace du texte dans l'éditeur.

  \param pRecherche Texte à rechercher
  \param pRemplacement Texte par lequel remplacer pRecherche
*/
void TextEdit::remplacement(TRecherche pRecherche) {
    QTextDocument::FindFlags flags = 0;
    if (pRecherche.casse)
        flags |= QTextDocument::FindCaseSensitively;
    if (pRecherche.motEntier)
        flags |= QTextDocument::FindWholeWords;
    if (getTextEdit()->find(pRecherche.recherche, flags)) {
        getTextEdit()->textCursor().removeSelectedText();
        int pos = getTextEdit()->textCursor().position();
        getTextEdit()->insertPlainText(pRecherche.remplacement);
        int newPos = getTextEdit()->textCursor().position();
        QTextCursor tmp = getTextEdit()->textCursor();
        tmp.setPosition(pos, QTextCursor::MoveAnchor);
        tmp.setPosition(newPos, QTextCursor::KeepAnchor);
        getTextEdit()->setTextCursor(tmp);
    } else if (pRecherche.complet) {
        flags |= QTextDocument::FindBackward;
        if (getTextEdit()->find(pRecherche.recherche, flags)) {
            getTextEdit()->textCursor().removeSelectedText();
            int pos = getTextEdit()->textCursor().position();
            getTextEdit()->insertPlainText(pRecherche.remplacement);
            int newPos = getTextEdit()->textCursor().position();
            QTextCursor tmp = getTextEdit()->textCursor();
            tmp.setPosition(pos, QTextCursor::MoveAnchor);
            tmp.setPosition(newPos, QTextCursor::KeepAnchor);
            getTextEdit()->setTextCursor(tmp);
        }
    }
}


/*! \brief Remplace toutes les occurences d'un texte dans l'éditeur.

  \param pRecherche Texte à rechercher
  \param pRemplacement Texte par lequel remplacer toutes les occurences de pRecherche
*/
void TextEdit::remplacerTout(TRecherche pRecherche) {
    QTextDocument::FindFlags flags = 0;
    if (pRecherche.casse)
        flags |= QTextDocument::FindCaseSensitively;
    if (pRecherche.motEntier)
        flags |= QTextDocument::FindWholeWords;
    pRecherche.complet = true;
    while (getTextEdit()->find(pRecherche.recherche, flags) || getTextEdit()->find(pRecherche.recherche, flags | QTextDocument::FindBackward))
        remplacement(pRecherche);
}


/*! \brief Surligne la ligne où le curseur est actuellement dans l'éditeur.

  \todo Permettre une couleur différente en mode pas à pas
*/
void TextEdit::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;

    QTextEdit::ExtraSelection selection;

    selection.format.setBackground(GestionnaireParametres::getInstance()->getCouleurLigneActuelle());
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = getTextEdit()->textCursor();
    selection.cursor.clearSelection();
    extraSelections.append(selection);

    getTextEdit()->setExtraSelections(extraSelections);
}


/*! \brief Réinitialise la coloration syntaxique.
*/
void TextEdit::changerCouleur() {
    m_color->deleteLater();
    m_color = new Coloration(getTextEdit()->document());
}


/*! \brief Charge les préférences de l'utilisateur et réinitialise l'éditeur avec ces paramètres.
*/
void TextEdit::loadSettings() {
    m_isLineNumberArea = GestionnaireParametres::getInstance()->getNumerotationLignes();
    m_isRetourLigne = GestionnaireParametres::getInstance()->getRetourLigne();
    m_tailleTab = GestionnaireParametres::getInstance()->getTailleTab();

    // Le layout actuel est supprimé afin de pouvoir afficher/masquer la barre de numérotation des lignes
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

    // Réinitialisation de la coloration syntaxique
    changerCouleur();
    getTextEdit()->setTabStopWidth(fontMetrics().width(QLatin1Char(' ')) * m_tailleTab);
    highlightCurrentLine();
    update();
    repaint();
}

void TextEdit::supprimerVariableGlossaire(QString pDesc) {
    QRegExp line;
    line.setPattern(pDesc);
    QTextCursor tc = getTextEdit()->document()->find(line);
    if (!tc.isNull()) {
        tc.select(QTextCursor::LineUnderCursor);
        tc.removeSelectedText();
        tc.deletePreviousChar();
    }
}
