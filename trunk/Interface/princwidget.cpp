#include "princwidget.h"

PrincWidget::PrincWidget()
{
    /* Outil de modification du fichier */
    m_zoneTexte = new TextEdit;

    m_quitter = new QPushButton ("&Quitter", this);

    m_fichier = new QFile(this);

    /* On ajoute une grille principale pour y insérer les différents objets */
    QGridLayout *m_princGrille = new QGridLayout (this);

    m_princGrille->addWidget(m_zoneTexte, 1,0);
    m_princGrille->addWidget(m_quitter, 2,2);

    setLayout(m_princGrille);

    QObject::connect(m_quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
}


void PrincWidget::ouvrirFichier()
{
    QString nomFichier = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), ".", "Algorithmes (*.algo);;Tous les fichiers (*);;Fichiers texte (*.txt)");

    ouvrirFichier(nomFichier);
}

void PrincWidget::ouvrirFichier(QString pNomFichier)
{
    m_fichier->setFileName(pNomFichier);

    if(!m_fichier->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    //On créer un flux de texte
    QTextStream flux(m_fichier);
    m_zoneTexte->setPlainText(flux.readAll());
    m_fichier->close();

    while (!m_zoneTexte->finFichier())
        qDebug() << m_zoneTexte->lectureLigne();
}

void PrincWidget::enregistrerFichier()
{
    if(!m_fichier->open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QString texte = m_zoneTexte->toPlainText();
    m_fichier->write(texte.toLocal8Bit());
    m_fichier->close();
}


