#include "textedit.h"

TextEdit::TextEdit() {
    setTabStopWidth(16);

    m_color = new Coloration(this);
}


void TextEdit::wheelEvent(QWheelEvent* pEvent) {
    if (!qApp->keyboardModifiers() & Qt::ControlModifier)
        QTextEdit::wheelEvent(pEvent);
    else if (pEvent->delta() > 0)
        zoomIn();
    else if (pEvent->delta() < 0)
        zoomOut();
}
