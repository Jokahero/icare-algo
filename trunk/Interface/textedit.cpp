#include "textedit.h"

TextEdit::TextEdit() {
    setTabStopWidth(16);
    m_ctrl = false;

    m_color = new Coloration(this);
}

void TextEdit::keyPressEvent(QKeyEvent* pEvent) {
    QTextEdit::keyPressEvent(pEvent);
    if (pEvent->key() == Qt::Key_Control)
        m_ctrl = true;
}

void TextEdit::keyReleaseEvent(QKeyEvent* pEvent) {
    QTextEdit::keyReleaseEvent(pEvent);
    if (pEvent->key() == Qt::Key_Control)
        m_ctrl = false;
}


void TextEdit::wheelEvent(QWheelEvent* pEvent) {
    if (!m_ctrl)
        QTextEdit::wheelEvent(pEvent);
    else if (pEvent->delta() > 0)
        zoomIn();
    else if (pEvent->delta() < 0)
        zoomOut();
}
