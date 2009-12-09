#ifndef ANALYSESYNTAXIQUE_H
#define ANALYSESYNTAXIQUE_H

#include <QtCore>

class Analyse;

/*! \brief  V√©rifier que chaque ligne du fichier soit convenablement structur√©e.
            exemple: regarde que ce soit bien "Pour i de 3 √  5 Faire" et non "Pour i de 3 5 √  Faire"
 */

class AnalyseSyntaxique : public QObject { //extends

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
};

#endif // ANALYSESYNTAXIQUE_H
