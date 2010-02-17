#include "analysesemantique.h"
#include "analyse.h"
#include <QtCore/QStack>
#include <QtCore/QDebug>

AnalyseSemantique::AnalyseSemantique(Analyse* pAnalyse) {
    m_analyse = pAnalyse;
    m_pileStructureControle = new QStack<Dictionnaire::typeLigne>();
    m_pilePosition = new QStack<int>();
}

AnalyseSemantique::~AnalyseSemantique() {
    delete m_pileStructureControle;
    delete m_pilePosition;
}

void AnalyseSemantique::lancer() {
    qDebug() << "Analyse sémantique lancée.";
    verifStruct();
    emit terminee();
    qDebug() << "Analyse sémantique terminée.";
}

void AnalyseSemantique::verifStruct() {
    for (int i = 0; i < m_analyse->getListeInstruction()->length(); i++) {
        Dictionnaire::typeLigne type = m_analyse->getListeInstruction()->at(i)->getTypeLigne();
        if (type == Dictionnaire::Debut || type == Dictionnaire::Si || type == Dictionnaire::TantQue || type == Dictionnaire::Pour || type == Dictionnaire::Repeter) {
            m_pileStructureControle->push(type);
            m_pilePosition->push(i);
        }
        
        else if (type == Dictionnaire::Fin) {
            if (m_pileStructureControle->top() == Dictionnaire::Debut)
                pop(i);
            else
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());

        } else if (type == Dictionnaire::FinSi) {
            if (m_pileStructureControle->top() == Dictionnaire::Si) {
                pop(i);
                if (m_analyse->getListeInstruction()->at(m_analyse->getListeInstruction()->at(i)->getLigneDebut())->getLigneMilieu() >= 0) {
                    int ligneSi = m_analyse->getListeInstruction()->at(i)->getLigneDebut();
                    int ligneSinon = m_analyse->getListeInstruction()->at(ligneSi)->getLigneMilieu();
                    int ligneFinSi = i;
                    m_analyse->getListeInstruction()->at(ligneFinSi)->setLigneMilieu(ligneSinon);
                    m_analyse->getListeInstruction()->at(ligneSinon)->setLigneFin(ligneFinSi);
                }
            } else
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());

        } else if (type == Dictionnaire::Sinon) {
            if (m_pileStructureControle->top() != Dictionnaire::Si)
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());
            else {
                m_analyse->getListeInstruction()->at(m_pilePosition->top())->setLigneMilieu(i);
                m_analyse->getListeInstruction()->at(i)->setLigneDebut(m_pilePosition->top());
                m_analyse->getListeInstruction()->at(i)->setLigneMilieu(i);
            }
        } else if (type == Dictionnaire::FinTantQue){
            if (m_pileStructureControle->top() == Dictionnaire::TantQue)
                pop(i);
            else
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());

        } else if (type == Dictionnaire::FinPour){
            if (m_pileStructureControle->top() == Dictionnaire::Pour)
                pop(i);
            else
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());

        } else if (type == Dictionnaire::Jusqua){
            if (m_pileStructureControle->top() == Dictionnaire::Repeter)
                pop(i);
            else
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());
        }
    }

    if (!m_pileStructureControle->empty())
        m_pileStructureControle->resize(0);
}

void AnalyseSemantique::pop(int i) {
    m_pileStructureControle->pop();
    int tmp = m_pilePosition->top();
    m_pilePosition->pop();
    m_analyse->getListeInstruction()->at(tmp)->setLigneDebut(tmp);
    m_analyse->getListeInstruction()->at(tmp)->setLigneFin(i);
    m_analyse->getListeInstruction()->at(i)->setLigneDebut(tmp);
    m_analyse->getListeInstruction()->at(i)->setLigneFin(i);
}
