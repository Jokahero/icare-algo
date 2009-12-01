#include "instruction.h"

Instruction::Instruction(int pNumLigne, QString pLigne, QString pCategorie) {
    m_numLigne = pNumLigne;
    m_ligne = pLigne;
    m_categorie = pCategorie;
}

int Instruction::getNumLigne() {
    return this->m_numLigne;
}

QString Instruction::getLigne() {
    return this->m_ligne;
}

QString Instruction::getCategorie() {
    return this->m_categorie;
}

void Instruction::setNumLigne(int pNumLigne) {
    this->m_numLigne = pNumLigne;
}

void Instruction::setLigne(QString pLigne) {
    this->m_ligne = pLigne;
}

void Instruction::setCategorie(QString pcategorie) {
    this->m_categorie = pcategorie;
}

