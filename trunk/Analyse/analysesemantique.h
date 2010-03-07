#ifndef ANALYSESEMANTIQUE_H
#define ANALYSESEMANTIQUE_H

#include <QObject>
#include "dictionnaire.h"
#include "analyse.h"

template <typename T> class QStack;


/** \brief Vérifie la cohérence d'un algorithme.

  Deux vérifications sont effectuées : imbrication de boucles/structures de contrôles, et l'initialisation des variables.
*/
class AnalyseSemantique : public QObject {
    Q_OBJECT

public:
    AnalyseSemantique(Analyse* pAnalyse);
    ~AnalyseSemantique();

private:
    Analyse* m_analyse;                                         /*!< \brief Pointeur vers l'instance d'analyse. */

    QStack<Dictionnaire::typeLigne>* m_pileStructureControle;   /*!< \brief Pile utilisée pour la vérification des imbrications de boucles/structures de contrôles. */
    QStack<int>* m_pilePosition;                                /*!< \brief Pile utilisée pour stocker les numéros de lignes lors de la vérification des imbrications. */
    QList<QString>* m_listeVariables;                           /*!< \brief Liste des variables initialisées. */

    bool verifStruct();
    void pop(int i);

    bool verifInitialisations();

public slots:
    void lancer();

signals:
    void terminee(bool pOk);
    void erreur(Analyse::erreur pErreur, int pNumLigne);
};

#endif // ANALYSESEMANTIQUE_H
