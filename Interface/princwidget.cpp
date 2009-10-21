#include "princwidget.h"

PrincWidget::PrincWidget()
{
    /* Outil de modification du fichier */
    m_zoneTexte = new TextEdit;

    m_quitter = new QPushButton ("&Quitter", this);

    /* On ajoute une grille principale pour y insérer les différents objets */
    QGridLayout *m_princGrille = new QGridLayout (this);

    m_princGrille->addWidget(m_zoneTexte, 1,0);
    m_princGrille->addWidget(m_quitter, 2,2);

    setLayout(m_princGrille);

    QObject::connect(m_quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
}
