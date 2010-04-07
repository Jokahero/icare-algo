#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "dictionnaire.h"

#include <QtCore/QString>

class Instruction {
public:
    Instruction(int pNumLigne, const QString& pLigne, Dictionnaire::typeLigne pTypeLigne, QStringList* pListeArgs = 0, int pLigneDebut = -1, int pLigneFin = -1, int pLigneMilieu = -1);
    ~Instruction();

    void setLigne(const QString& pLigne);
    void setNumLigne(int pNumLigne);
    int getNumLigne() const;
    QString getLigne() const;
    Dictionnaire::typeLigne getTypeLigne() const;
    void setTypeLigne(Dictionnaire::typeLigne pTypeLigne);
    QStringList* getArgs() const;
    int getLigneDebut() const;
    int getLigneMilieu() const;
    int getLigneFin() const;
    void setLigneDebut(int pLigne);
    void setLigneMilieu(int pLigne);
    void setLigneFin(int pLigne);

private:
    QString m_ligne;
    int m_numLigne;
    Dictionnaire::typeLigne m_typeLigne;
    int m_ligneDebut;
    int m_ligneMilieu;
    int m_ligneFin;
    QStringList* m_args;
};

#endif // INSTRUCTION_H
