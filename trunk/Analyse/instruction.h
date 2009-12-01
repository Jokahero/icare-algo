#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QtCore>

class Instruction
{
public:
    Instruction(int pNumLigne, QString pLigne, QString pCategorie);

    void setLigne(QString pLigne);
    void setNumLigne(int pNumLigne);
    int getNumLigne();
    QString getLigne();
    QString getCategorie();
    void setCategorie(QString pcategorie);

private:
    QString m_ligne;
    int m_numLigne;
    QString m_categorie;
};

#endif // INSTRUCTION_H
