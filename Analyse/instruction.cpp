#include "instruction.h"

#include <QtCore/QStringList>

Instruction::Instruction(int pNumLigne, QString pLigne, Dictionnaire::typeLigne pTypeLigne, QStringList* pListeArgs, int pLigneDebut, int pLigneFin) {
    m_numLigne = pNumLigne;
    m_ligne = pLigne;
    m_typeLigne = pTypeLigne;
    m_ligneDebut = pLigneDebut;
    m_ligneFin = pLigneFin;
    m_args = pListeArgs;
}

Instruction::~Instruction() {
    delete m_args;
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

QStringList* Instruction::getArgs() {
    return m_args;
}
