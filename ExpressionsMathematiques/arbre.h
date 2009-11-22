#ifndef ARBRE_H
#define ARBRE_H

#include <QtCore>

#include "MathExp_global.h"

/*! \brief Implémente les arbres binaires.
*/
class ARBRESHARED_EXPORT Arbre {
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
    QString m_contenu;              /*!<\brief Expression contenue dans ce noeud de l'arbre. Elle peut être soit un opérateur si l'arbre n'est pas une feuille, soit une valeur numérique. */
    Arbre* m_sag;                   /*!<\brief Pointeur vers le sous arbre gauche. */
    Arbre* m_sad;                   /*!<\brief Pointeur vers le sous arbre droit. */
};

#endif // ARBRE_H
