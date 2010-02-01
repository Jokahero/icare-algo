#include "instruction.h"

Instruction::Instruction(int pNumLigne, QString pLigne, Dictionnaire::typeLigne pTypeLigne) {
    m_numLigne = pNumLigne;
    m_ligne = pLigne;
    m_typeLigne = pTypeLigne;
}

int Instruction::getNumLigne() {
    return m_numLigne;
}

QString Instruction::getLigne() {
    return m_ligne;
}

Dictionnaire::typeLigne Instruction::getTypeLigne() {
    return m_typeLigne;
}

void Instruction::setNumLigne(int pNumLigne) {
    m_numLigne = pNumLigne;
}

void Instruction::setLigne(QString pLigne) {
    m_ligne = pLigne;
}

void Instruction::setTypeLigne(Dictionnaire::typeLigne pTypeLigne) {
    m_typeLigne = pTypeLigne;
}

