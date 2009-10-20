#include "princwidget.h"

PrincWidget::PrincWidget()
{
    /* Boutons de tests */
    m_testSyntaxe = new QPushButton (tr("Tester la &syntaxe"), this);
    m_testOperation = new QPushButton (tr("Tester les &operations"), this);
    m_testComplet = new QPushButton (tr("Executer le test complet"), this);

    /* On ajoute un groupe et une grille pour les boutons */
    QGroupBox *m_groupeTest = new QGroupBox (this);
    QGridLayout *m_layoutTest = new QGridLayout (this);

    /* On place les boutons dans la grille */
    m_layoutTest->addWidget(m_testSyntaxe, 0, 0);
    m_layoutTest->addWidget(m_testOperation, 1, 0);
    m_layoutTest->addWidget(m_testComplet, 2, 0);

    /* On place la grille dans le groupe */
    m_groupeTest->setLayout(m_layoutTest);
    m_groupeTest->setFixedSize(185,100);

    /* Outils de selection du fichier */
    m_fichier = new QLineEdit (tr("Fichier"), this);
    m_parcourir = new QPushButton (this);
    m_parcourir->setFixedSize(25,25);

    /* Outil de modification du fichier */
    m_zoneTexte = new TextEdit;

    m_quitter = new QPushButton ("&Quitter", this);

    /* On ajoute une grille principale pour y insérer les différents objets */
    QGridLayout *m_princGrille = new QGridLayout (this);

    m_princGrille->addWidget(m_fichier, 0,0);
    m_princGrille->addWidget(m_parcourir,0,1);
    m_princGrille->addWidget(m_groupeTest,0,2);
    m_princGrille->addWidget(m_zoneTexte, 1,0);
    m_princGrille->addWidget(m_quitter, 2,2);

    setLayout(m_princGrille);

    QObject::connect(m_quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
}
