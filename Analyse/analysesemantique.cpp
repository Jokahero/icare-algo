#include "analysesemantique.h"
#include "analyse.h"
#include <QtCore/QStack>
#include <QtCore/QDebug>

AnalyseSemantique::AnalyseSemantique(Analyse* pAnalyse) {
    m_analyse = pAnalyse;
    m_pileStructureControle = new QStack<Dictionnaire::typeLigne>();
}

void AnalyseSemantique::lancer() {
    qDebug() << "Analyse sémantique lancée.";
    verifStruct();
    emit terminee();
    qDebug() << "Analyse sémantique terminée.";
}

// TODO : numéro de ligne à la fin
void AnalyseSemantique::verifStruct() {
    qDebug() << "Début : " << Dictionnaire::Debut;
    qDebug() << "Fin : " << Dictionnaire::Fin;
    for (int i = 0; i < m_analyse->getListeInstruction()->length(); i++) {
        Dictionnaire::typeLigne type = m_analyse->getListeInstruction()->at(i)->getTypeLigne();
        qDebug() << i << " : " << type;
        if (type == Dictionnaire::Debut || type == Dictionnaire::Si || type == Dictionnaire::TantQue || type == Dictionnaire::Pour || type == Dictionnaire::Repeter)
            m_pileStructureControle->push(type);
        
        else if (type == Dictionnaire::Fin) {
            if (m_pileStructureControle->top() == Dictionnaire::Debut)
                m_pileStructureControle->pop();
            else
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());

        } else if (type == Dictionnaire::FinSi) {
            if (m_pileStructureControle->top() == Dictionnaire::Si)
                m_pileStructureControle->pop();
            else
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());

        } else if (type == Dictionnaire::Sinon) {
            if (m_pileStructureControle->top() != Dictionnaire::Si)
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());

        } else if (type == Dictionnaire::FinTantQue){
            if (m_pileStructureControle->top() == Dictionnaire::TantQue)
                m_pileStructureControle->pop();
            else
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());

        } else if (type == Dictionnaire::FinPour){
            if (m_pileStructureControle->top() == Dictionnaire::Pour)
                m_pileStructureControle->pop();
            else
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());

        } else if (type == Dictionnaire::Jusqua){
            if (m_pileStructureControle->top() == Dictionnaire::Repeter)
                m_pileStructureControle->pop();
            else
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());
        }
    }

    if (!m_pileStructureControle->empty()) {
        emit erreur(Analyse::Struct, 42);
        m_pileStructureControle->resize(0);
    }
}
