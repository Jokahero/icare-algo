#include "barrenombres.h"

#include <QtGui/QAbstractTextDocumentLayout>
#include <QtGui/QPainter>
#include <QtGui/QScrollBar>
#include <QtGui/QTextBlock>
#include <QtGui/QTextEdit>

BarreNombres::BarreNombres(QWidget *pParent) : QWidget(pParent), m_edit(0) {
    // On définit l'espace à 4 nombres
    setFixedWidth(fontMetrics().width(QString("0000")));
}

void BarreNombres::setTextEdit(QTextEdit *pEdit) {
    m_edit = pEdit;
    connect(m_edit->document()->documentLayout(), SIGNAL(update(const QRectF &)), this, SLOT(update()));
    connect(m_edit->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(update()));
}

void BarreNombres::paintEvent(QPaintEvent */*pEvent*/) {
    QAbstractTextDocumentLayout *layout = m_edit->document()->documentLayout();
    int contentsY = m_edit->verticalScrollBar()->value();
    qreal pageBottom = contentsY + m_edit->viewport()->height();
    const QFontMetrics fm = fontMetrics();
    const int ascent = fontMetrics().ascent() + 1;
    int lineCount = 1;

    QPainter p(this);

    for (QTextBlock block = m_edit->document()->begin(); block.isValid(); block = block.next(), lineCount++) {
        const QRectF boundingRect = layout->blockBoundingRect(block);

        QPointF position = boundingRect.topLeft();
        if (position.y() + boundingRect.height() < contentsY)
            continue;
        if (position.y() > pageBottom)
            break;

        const QString txt = QString::number(lineCount);
        p.drawText(width() - fm.width(txt), qRound(position.y()) - contentsY + ascent, txt);
    }
}
