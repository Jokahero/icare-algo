#ifndef ANALYSESYNTAXIQUE_H
#define ANALYSESYNTAXIQUE_H

#include <QtCore>
#include "Analyse_global.h"
#include "glossaire.h"

class ANALYSESYNTAXIQUESHARED_EXPORT AnalyseSyntaxique : public QObject {

    Q_OBJECT

public:
    AnalyseSyntaxique();
    Glossaire* getGlossaire();

public slots:
    void lancer(QFile* pFichier);

private:
    void lectureGlossaire(QFile* pFichier);
    Glossaire* m_glossaire;

signals:
    void terminee();
};

#endif // ANALYSESYNTAXIQUE_H
