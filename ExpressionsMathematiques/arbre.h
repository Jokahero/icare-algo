#ifndef ARBRE_H
#define ARBRE_H

#include <QtCore>

class Arbre {
public:
    Arbre();
    Arbre(QString pContenu, Arbre* pSag, Arbre* pSad);

    // Observateurs
    Arbre* getSag();
    Arbre* getSad();
    QString getContenu();
    bool estFeuille();
    unsigned int hauteur();

    void afficher();

    // Modificateurs
    void setSag(Arbre* pSag);
    void setSad(Arbre* pSad);
    void setContenu(QString pContenu);

private:
    QString m_contenu;
    Arbre* m_sag;
    Arbre* m_sad;
};

#endif // ARBRE_H
