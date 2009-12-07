#ifndef ANALYSE_H
#define ANALYSE_H

#include <QObject>
#include <QList>
#include "Analyse_global.h"
#include "instruction.h"
#include "dictionnaire.h"
#include "glossaire.h"
#include "analysesemantique.h"
#include "analysesyntaxique.h"

class ANALYSESHARED_EXPORT Analyse : public QObject {

    Q_OBJECT

public:
    Analyse();
    Glossaire* getGlossaire();
    QList<Instruction*>* getListeInstruction();

    void setDebutGlossaire(int pNumLigne);
    void setFinGlossaire(int pNumLigne);
    void setDebutAlgo(int pNumLigne);
    void setFinAlgo(int pNumLigne);

    int getDebutGlossaire();
    int getFinGlossaire();
    int getDebutAlgo();
    int getFinAlgo();

public slots:
    void lancerAnalyseSyntaxique(QFile* pFichier);
    void lancerAnalyseSemantique(QFile* pFichier);

signals:
    void sigLancerAnalyseSyntaxique(QFile* pFichier);
    void sigLancerAnalyseSemantique(QFile* pFichier);

private:
    QList<Instruction*>* m_listeInstruction;
    Dictionnaire* m_dictionnaire;
    Glossaire* m_glossaire;
    AnalyseSyntaxique* m_analyseSyntaxique;
    AnalyseSemantique* m_analyseSemantique;
    int m_debutGlossaire;
    int m_finGlossaire;
    int m_debutAlgo;
    int m_finAlgo;
};

#endif // ANALYSE_H
