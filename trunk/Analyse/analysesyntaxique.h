#ifndef ANALYSESYNTAXIQUE_H
#define ANALYSESYNTAXIQUE_H

#include "analyse.h"

#include <QtCore/QObject>

class QFile;

/*! \brief  Vérifier que chaque ligne du fichier soit convenablement structurée.
            Exemple : Vérifie que ce soit bien "Pour i de 3 à 5 Faire" et non "Pour i de 3 5 à Faire"
 */

class AnalyseSyntaxique : public QObject {
    Q_OBJECT

public:
    AnalyseSyntaxique(Analyse* pAnalyse);

public slots:
    void lancer(QFile* pFichier);

private:
    bool lectureGlossaire(QFile* pFichier);
    bool lectureInstructions(QFile* pFichier);
    Analyse* m_analyse;

signals:
    void terminee(bool);
    void erreur(Analyse::erreur pErreur, int pNumLigne);
};

#endif // ANALYSESYNTAXIQUE_H
