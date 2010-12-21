#include "boutoncouleur.h"

#include <QtGui/QColor>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QPalette>
#include <QtGui/QPen>


/*! \brief Constructeur. Initialise un bouton de taille 25×25.

  \param parent Widget parent
*/
BoutonCouleur::BoutonCouleur(QWidget *parent) : QWidget(parent) {
    setAutoFillBackground(true);
    setMinimumSize(25, 25);
}


/*! \brief Définit la couleur du bouton.

  \param pCouleur Couleur à appliquer
*/
void BoutonCouleur::setCouleur(QColor pCouleur) {
    QPalette pal = palette();
    pal.setColor(backgroundRole(), pCouleur);
    setPalette(pal);
    repaint();
}


/*! \brief Redéfinit l'évènement du clic souris.

  Si le clic est fait avec le bouton gauche de la souris, le signal clicked() est émit. Sinon, l'évènement normal d'un QWidget est exécuté.
  \param pE Évènement à traîter
*/
void BoutonCouleur::mousePressEvent(QMouseEvent *pE) {
    if (pE->button() == Qt::LeftButton)
        emit clicked();
    else
        QWidget::mousePressEvent(pE);
}


/*! \brief Redéfinit l'évènement de dessin.

  Dessine un carré de la couleur du bouton, et un cadre noir de 1px de large autour.
  \param pE Évènement à traîter
*/
void BoutonCouleur::paintEvent(QPaintEvent *pE) {
    QWidget::paintEvent(pE);
    QPainter painter;
    QPen pen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.begin(this);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(0, 0, width() - 1, height() - 1);
    painter.end();
}


/*! \brief Retourne la couleur du bouton.

  \return couleur actuelle du bouton.
*/
QColor BoutonCouleur::getCouleur() {
    return palette().color(backgroundRole());
}
