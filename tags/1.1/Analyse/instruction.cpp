#include "instruction.h"

#include <QtCore/QStringList>

Instruction::Instruction(int pNumLigne, const QString& pLigne, Dictionnaire::typeLigne pTypeLigne, QStringList* pListeArgs, int pLigneDebut, int pLigneFin, int pLigneMilieu) {
    m_numLigne = pNumLigne;
    m_ligne = pLigne;
    m_typeLigne = pTypeLigne;
    m_ligneDebut = pLigneDebut;
    m_ligneMilieu = pLigneMilieu;
    m_ligneFin = pLigneFin;
    m_args = pListeArgs;
}

Instruction::~Instruction() {
    delete m_args;
}

int Instruction::getNumLigne() const {
    return m_numLigne;
}

QString Instruction::getLigne() const {
    return m_ligne;
}

Dictionnaire::typeLigne Instruction::getTypeLigne() const {
    return m_typeLigne;
}

void Instruction::setNumLigne(int pNumLigne) {
    m_numLigne = pNumLigne;
}

void Instruction::setLigne(const QString& pLigne) {
    m_ligne = pLigne;
}

void Instruction::setTypeLigne(Dictionnaire::typeLigne pTypeLigne) {
    m_typeLigne = pTypeLigne;
}

QStringList* Instruction::getArgs() const {
    return m_args;
}

int Instruction::getLigneDebut() const {
    return m_ligneDebut;
}

int Instruction::getLigneFin() const {
    return m_ligneFin;
}

void Instruction::setLigneDebut(int pLigne) {
    m_ligneDebut = pLigne;
}

void Instruction::setLigneFin(int pLigne) {
    m_ligneFin = pLigne;
}

void Instruction::setLigneMilieu(int pLigne) {
    m_ligneMilieu = pLigne;
}

int Instruction::getLigneMilieu() const {
    return m_ligneMilieu;
}
