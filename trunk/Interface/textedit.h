#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QtGui>
#include "coloration.h"

/*! \brief Zone de texte permettant d'afficher et de modifier le contenu du fichier
*/
class TextEdit : public QTextEdit {
    Q_OBJECT
public:
    TextEdit();

private:
    Coloration *m_color;
    void wheelEvent(QWheelEvent* pEvent);
};

#endif // TEXTEDIT_H
