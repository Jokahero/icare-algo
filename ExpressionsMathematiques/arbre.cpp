#include "arbre.h"

Arbre::Arbre() {
    m_sag = NULL;
    m_sad = NULL;
    m_contenu = QString::null;
}

Arbre::Arbre(QString pContenu, Arbre* pSag, Arbre* pSad) {
    m_sag = pSag;
    m_sad = pSad;
    m_contenu = pContenu;
}

Arbre* Arbre::getSag() {
    return m_sag;
}

Arbre* Arbre::getSad() {
    return m_sad;
}

QString Arbre::getContenu() {
    return m_contenu;
}

bool Arbre::estFeuille() {
    return (m_sag == NULL);
}

unsigned int Arbre::hauteur() {
    if (estFeuille())
        return 0;
    if (getSag()->hauteur() > getSad()->hauteur())
        return (getSag()->hauteur() + 1);
    else
        return (getSad()->hauteur() + 1);
}

void Arbre::setSag(Arbre* pSag) {
    m_sag = pSag;
}

void Arbre::setSad(Arbre* pSad) {
    m_sad = pSad;
}

void Arbre::setContenu(QString pContenu) {
    m_contenu = pContenu;
}

void Arbre::afficher() {
    qDebug() << "Hauteur : " << hauteur() << " : " << getContenu();
    if (!estFeuille()) {
        getSag()->afficher();
        getSad()->afficher();
    }
}
