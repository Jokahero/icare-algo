#include "arbre.h"

#include <QtCore/QDebug>

/*! \brief Construit un arbre vide.

  Initialise les sous-arbres à NULL, et une chaîne vide comme contenu.
*/
Arbre::Arbre() {
    m_sag = NULL;
    m_sad = NULL;
    m_contenu = QString::null;
}

/*! \brief Construit un arbre comportant des sous arbres.

  \param pContenu Le contenu du noeud.
  \param pSag Pointeur vers le sous-arbre gauche.
  \param pSad Pointeur vers le sous-arbre droit.
*/
Arbre::Arbre(const QString& pContenu, Arbre* pSag, Arbre* pSad) {
    m_sag = pSag;
    m_sad = pSad;
    m_contenu = pContenu;
}

Arbre::~Arbre() {
    delete m_sag;
    delete m_sad;
}

/*! \brief Retourne le sous-arbre gauche.

  Si l'arbre est vide, retourne NULL.
  \return Le sous-arbre gauche, ou NULL.
*/
Arbre* Arbre::getSag() {
    return m_sag;
}

/*! \brief Retourne le sous-arbre droit.

  Si l'arbre est vide, retourne NULL.
  \return Le sous-arbre droit, ou NULL.
*/
Arbre* Arbre::getSad() {
    return m_sad;
}

/*! \brief Retourne le contenu du noeud.

  Si il n'y a pas de contenu, retourne une chaîne vide.
  \return Le contenu du noeud.
*/
QString Arbre::getContenu() {
    return m_contenu;
}

/*! \brief Indique si l'arbre est vide.

  \return Vrai si l'arbre est vide, faux sinon.
*/
bool Arbre::estFeuille() {
    return (m_sag == NULL);
}

/*! \brief Retourne la hauteur de l'arbre.

  \return La hauteur de l'arbre.
*/
unsigned int Arbre::hauteur() {
    if (estFeuille())
        return 0;
    if (getSag()->hauteur() > getSad()->hauteur())
        return (getSag()->hauteur() + 1);
    else
        return (getSad()->hauteur() + 1);
}

/*! \brief Définit le sous-arbre gauche de l'arbre.

  \param pSag Le nouveau sous-arbre gauche.
*/
void Arbre::setSag(Arbre* pSag) {
    m_sag = pSag;
}

/*! \brief Définit le sous-arbre droit de l'arbre.

  \param pSad Le nouveau sous-arbre droit.
*/
void Arbre::setSad(Arbre* pSad) {
    m_sad = pSad;
}

/*! \brief Définit le contenu de l'arbre.

  \param pContenu Le nouveau contenu.
*/
void Arbre::setContenu(const QString& pContenu) {
    m_contenu = pContenu;
}
