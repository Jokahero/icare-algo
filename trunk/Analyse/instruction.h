#ifndef INSTRUCTION_H
#define INSTRUCTION_H

class Instruction
{
public:
    Instruction(int pNumLigne, QString pLigne);
    void setLigne();
    void setNumLigne();

private:
    QString m_ligne;
    QString m_numLigne;
};

#endif // INSTRUCTION_H
