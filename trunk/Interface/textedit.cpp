#include "textedit.h"

#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtGui/QPainter>

TextEdit::TextEdit() {
    m_color = new Coloration(document());

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



void TextEdit::highlightCurrentLine() {
    QSettings settings;
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor;
        lineColor.setNamedColor(settings.value("Coloration ligne actuelle").toString());

        selection.format.setBackground(lineColor);
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
    QSettings settings;
    m_isLineNumberArea = settings.value("NumerotationLignes").toBool();
    m_isRetourLigne = settings.value("RetourLigne").toBool();
    m_tailleTab = settings.value("TailleTab").toInt();

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
