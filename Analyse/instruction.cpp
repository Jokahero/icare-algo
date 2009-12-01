#include "instruction.h"

Instruction::Instruction(int pNumLigne, QString pLigne, QString pCategorie) {
    m_numLigne = pNumLigne;
    m_ligne = pLigne;
    m_categorie = pCategorie;
}

int Instruction::getNumLigne() {
    return m_numLigne;
}

QString Instruction::getLigne() {
    return m_ligne;
}

QString Instruction::getCategorie() {
    return m_categorie;
}

void Instruction::setNumLigne(int pNumLigne) {
    m_numLigne = pNumLigne;
}

void Instruction::setLigne(QString pLigne) {
    m_ligne = pLigne;
}

void Instruction::setCategorie(QString pCategorie) {
    m_categorie = pCategorie;
}

