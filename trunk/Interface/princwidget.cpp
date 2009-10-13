#include "princwidget.h"

PrincWidget::PrincWidget()
{
    // Tests
    m_testSyntaxe = new QPushButton (tr("Tester la &syntaxe"), this);
    m_testOperation = new QPushButton (tr("Tester les &operations"), this);
    m_testComplet = new QPushButton (tr("Executer le test complet"), this);

    QGroupBox *m_groupeTest = new QGroupBox (this);
    QGridLayout *m_layoutTest = new QGridLayout (this);

    m_layoutTest->addWidget(m_testSyntaxe, 0, 0);
    m_layoutTest->addWidget(m_testOperation, 1, 0);
    m_layoutTest->addWidget(m_testComplet, 2, 0);

    m_groupeTest->setLayout(m_layoutTest);
    m_groupeTest->setFixedSize(185,100);

    // Selection du fichier
    m_fichier = new QLineEdit (tr("Fichier"), this);
    m_parcourir = new QPushButton (this);
    m_parcourir->setFixedSize(25,25);

    QGridLayout *m_princGrille = new QGridLayout (this);

    m_princGrille->addWidget(m_fichier, 0,0);
    m_princGrille->addWidget(m_parcourir,0,1);
    m_princGrille->addWidget(m_groupeTest,1,1);

    setLayout(m_princGrille);
}
