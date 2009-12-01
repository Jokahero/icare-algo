#ifndef ANALYSE_H
#define ANALYSE_H

#include <QObject>
#include <QList>
#include "Analyse_global.h"
#include "instruction.h"
#include "dictionnaire.h"
#include "glossaire.h"

class AnalyseSyntaxique;
class AnalyseSemantique;

class ANALYSESHARED_EXPORT Analyse : public QObject {

    Q_OBJECT

public:
    Analyse();
    Glossaire* getGlossaire();

public slots:
    void lancerAnalyseSyntaxique(QFile* pFichier);
    void lancerAnalyseSemantique(QFile* pFichier);

signals:
    void sigLancerAnalyseSyntaxique(QFile* pFichier);
    void sigLancerAnalyseSemantique(QFile* pFichier);

private:
    QList<Instruction*> m_listeInstruction;
    Dictionnaire* m_dictionnaire;
    Glossaire* m_glossaire;
    AnalyseSyntaxique* m_analyseSyntaxique;
    AnalyseSemantique* m_analyseSemantique;
};

#endif // ANALYSE_H
