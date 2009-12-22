#ifndef ANALYSESYNTAXIQUE_H
#define ANALYSESYNTAXIQUE_H

#include <QtCore>

class Analyse;

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
    void lectureGlossaire(QFile* pFichier);
    void lectureInstructions(QFile* pFichier);
    Analyse* m_analyse;

signals:
    void terminee();
    void erreur(int pNumLigne);
};

#endif // ANALYSESYNTAXIQUE_H
