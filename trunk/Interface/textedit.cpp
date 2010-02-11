#include "textedit.h"

#include "coloration.h"
#include "gestionnaireparametres.h"
#include "window.h"

#include <QtCore/QDebug>
#include <QtGui/QPainter>

TextEdit::TextEdit(Window* parent) : m_parent(parent) {
    m_color = new Coloration(document());
    setAcceptDrops(true);

    m_lineNumberArea = new LineNumberArea(this);

    loadSettings();

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(const QRect &, int)), this, SLOT(updateLineNumberArea(const QRect &, int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}


void TextEdit::wheelEvent(QWheelEvent* pEvent) {
    //if (!qApp->keyboardModifiers() && Qt::ControlModifier)
    QPlainTextEdit::wheelEvent(pEvent);
    /*else if (pEvent->delta() > 0)
        zoomIn();
    else if (pEvent->delta() < 0)
        zoomOut();*/
}

/*******************************************************/

int TextEdit::lineNumberAreaWidth() {
    if (m_isLineNumberArea) {
        int digits = 1;
        int max = qMax(1, blockCount());
        while (max >= 10) {
            max /= 10;
            ++digits;
        }

        int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;
        return space;
    } else
        return 0;
}



void TextEdit::updateLineNumberAreaWidth(int /* newBlockCount */) {
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}



void TextEdit::updateLineNumberArea(const QRect &rect, int dy) {
    if (m_isLineNumberArea) {
        if (dy)
            m_lineNumberArea->scroll(0, dy);
        else
            m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());

        if (rect.contains(viewport()->rect()))
            updateLineNumberAreaWidth(0);
    }
}



void TextEdit::resizeEvent(QResizeEvent *e) {
    QPlainTextEdit::resizeEvent(e);

    if (m_isLineNumberArea) {
        QRect cr = contentsRect();
        m_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
    }
}


void TextEdit::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasFormat("text/plain")) {
        m_parent->ouvrirFichier(mimeData->text().trimmed().replace("file://", ""));
        event->accept();
    }
}



void TextEdit::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        selection.format.setBackground(GestionnaireParametres::getInstance()->getCouleurLigneActuelle());
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}



void TextEdit::lineNumberAreaPaintEvent(QPaintEvent *event) {
    if (m_isLineNumberArea) {
        QPainter painter(m_lineNumberArea);
        painter.fillRect(event->rect(), Qt::lightGray);


        QTextBlock block = firstVisibleBlock();
        int blockNumber = block.blockNumber();
        int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
        int bottom = top + (int) blockBoundingRect(block).height();

        while (block.isValid() && top <= event->rect().bottom()) {
            if (block.isVisible() && bottom >= event->rect().top()) {
                QString number = QString::number(blockNumber + 1);
                painter.setPen(Qt::black);
                painter.drawText(0, top, m_lineNumberArea->width(), fontMetrics().height(),
                                 Qt::AlignRight, number);
            }

            block = block.next();
            top = bottom;
            bottom = top + (int) blockBoundingRect(block).height();
            ++blockNumber;
        }
    }
}

void TextEdit::changerCouleur() {
    m_color->deleteLater();
    m_color = new Coloration(document());
}

void TextEdit::loadSettings() {
    m_isLineNumberArea = GestionnaireParametres::getInstance()->getNumerotationLignes();
    m_isRetourLigne = GestionnaireParametres::getInstance()->getRetourLigne();
    m_tailleTab = GestionnaireParametres::getInstance()->getTailleTab();

    emit blockCountChanged(blockCount());
    if (m_isRetourLigne)
    setLineWrapMode(QPlainTextEdit::WidgetWidth);
    else
        setLineWrapMode(QPlainTextEdit::NoWrap);
    changerCouleur();
    setTabStopWidth(fontMetrics().width(QLatin1Char(' ')) * m_tailleTab);
    highlightCurrentLine();
    update();
    repaint();
}

void TextEdit::changementLigne(int pNumLigne) {
    QTextBlock block;
    QTextCursor cursor;
    QTextBlockFormat blockFormat;

    block = document()->findBlockByLineNumber(pNumLigne - 1);
    cursor = QTextCursor(block);
    blockFormat = cursor.blockFormat();
    blockFormat.clearBackground();
    cursor.setBlockFormat(blockFormat);
    setTextCursor(cursor);
}
