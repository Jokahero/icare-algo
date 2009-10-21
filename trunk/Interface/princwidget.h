#ifndef PRINCWIDGET_H
#define PRINCWIDGET_H

#include <QtGui>
#include <QWidget>

#include "textedit.h"
/*! \brief Widget principal
  */
class PrincWidget : public QWidget
{
    Q_OBJECT

public:
    PrincWidget();

    // Modification du fichier
    TextEdit *m_zoneTexte;

    QFile m_fichier;

    QPushButton *m_quitter;

    public slots:
        void ouvrirFichier();
};

#endif // PRINCWIDGET_H
