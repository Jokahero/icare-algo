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


void PrincWidget::ouvrirFichier()
{
    QString m_nomFichier = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), ".", "Algorithmes (*.algo)");
    m_fichier.setFileName(m_nomFichier);

    if(!m_fichier.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    //On créer un flux de texte
    QTextStream flux(&m_fichier);
    m_zoneTexte->setPlainText(flux.readAll());
    m_fichier.close();
}

void PrincWidget::enregistrerFichier()
{
    if(!m_fichier.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QString texte = m_zoneTexte->toPlainText();
    m_fichier.write(texte.toLocal8Bit());
    m_fichier.close();
}
