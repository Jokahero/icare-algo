#ifndef PRINCWIDGET_H
#define PRINCWIDGET_H

#include <QtGui>
#include <QWidget>

#include "textedit.h"
/*! \brief Widget principal
  */
class PrincWidget : public QWidget
{

public:
    PrincWidget();

    // Modification du fichier
    TextEdit *m_zoneTexte;

    QPushButton *m_quitter;
};

#endif // PRINCWIDGET_H
