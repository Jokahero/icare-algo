#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "dictionnaire.h"
#include <QtCore>

class Instruction
{
public:
    Instruction(int pNumLigne, QString pLigne, Dictionnaire::typeLigne pTypeLigne);

    void setLigne(QString pLigne);
    void setNumLigne(int pNumLigne);
    int getNumLigne();
    QString getLigne();
    Dictionnaire::typeLigne getTypeLigne();
    void setTypeLigne(Dictionnaire::typeLigne pTypeLigne);

private:
    QString m_ligne;
    int m_numLigne;
    Dictionnaire::typeLigne m_typeLigne;
};

#endif // INSTRUCTION_H
