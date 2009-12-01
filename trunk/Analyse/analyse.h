#ifndef ANALYSE_H
#define ANALYSE_H

#include <QObject>
#include <QList>
#include "instruction.h"
#include "dictionnaire.h"
#include "glossaire.h"

class AnalyseSyntaxique;
class AnalyseSemantique;
class Analyse : public QObject
{
public:
    Analyse();
    Glossaire* getGlossaire();

private:
    QList<Instruction*> m_listeInstruction;
    Dictionnaire* m_dico;
    Glossaire* m_glossaire;
    AnalyseSyntaxique* m_analyseSyntaxique;
    AnalyseSemantique* m_analyseSemantique;
};

#endif // ANALYSE_H
