#ifndef ANALYSESYNTAXIQUE_H
#define ANALYSESYNTAXIQUE_H

#include <QtCore>
#include "Analyse_global.h"
#include "glossaire.h"
#include "../Interface/textedit.h"

class ANALYSESYNTAXIQUESHARED_EXPORT AnalyseSyntaxique : public QObject {

    Q_OBJECT

public:
    AnalyseSyntaxique(TextEdit* pTextEdit);
    Glossaire* getGlossaire();

public slots:
    void lancer();

private:
    void lectureGlossaire();
    Glossaire* m_glossaire;
    TextEdit* m_zoneTexte;

signals:
    void terminee();
};

#endif // ANALYSESYNTAXIQUE_H
