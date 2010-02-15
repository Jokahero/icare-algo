#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "dictionnaire.h"

#include <QtCore/QString>

class Instruction {
public:
    Instruction(int pNumLigne, QString pLigne, Dictionnaire::typeLigne pTypeLigne, QStringList* pListeArgs = 0, int pLigneDebut = -1, int pLigneFin = -1);
    ~Instruction();

    void setLigne(QString pLigne);
    void setNumLigne(int pNumLigne);
    int getNumLigne();
    QString getLigne();
    Dictionnaire::typeLigne getTypeLigne();
    void setTypeLigne(Dictionnaire::typeLigne pTypeLigne);
    QStringList* getArgs();
    int getLigneDebut();
    int getLigneFin();
    void setLigneDebut(int pLigne);
    void setLigneFin(int pLigne);

private:
    QString m_ligne;
    int m_numLigne;
    Dictionnaire::typeLigne m_typeLigne;
    int m_ligneDebut;
    int m_ligneFin;
    QStringList* m_args;
};

#endif // INSTRUCTION_H
