#ifndef BOUTONCOULEUR_H
#define BOUTONCOULEUR_H

#include <QtGui/QWidget>

class QColor;
class QMouseEvent;
class QPaintEvent;

class BoutonCouleur : public QWidget {
    Q_OBJECT

public:
    BoutonCouleur(QWidget *parent = 0);
    QColor getCouleur();

protected:
    void mousePressEvent(QMouseEvent *pE);
    void paintEvent(QPaintEvent *pE);

public slots:
    void setCouleur(QColor pCouleur);

signals:
    void clicked();
};

#endif // BOUTONCOULEUR_H
