#include "boutoncouleur.h"

#include <QtCore/QDebug>
#include <QtGui/QColor>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QPalette>
#include <QtGui/QPen>

BoutonCouleur::BoutonCouleur(QWidget *parent) : QWidget(parent) {
    setAutoFillBackground(true);
    setFixedSize(25, 25);
}

void BoutonCouleur::setCouleur(QColor pColor) {
    QPalette pal = palette();
    pal.setColor(backgroundRole(), pColor);
    setPalette(pal);
    repaint();
}

void BoutonCouleur::mousePressEvent(QMouseEvent *pE) {
    if (pE->button() == Qt::LeftButton)
        emit clicked();
    else
        QWidget::mousePressEvent(pE);
}

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

QColor BoutonCouleur::getCouleur() {
    return palette().color(backgroundRole());
}
