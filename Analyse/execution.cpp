#include "execution.h"

#include "expressionlogique.h"
#include "glossaire.h"
#include "mathexp.h"
#include "../Interface/fenetresaisie.h"

#include <QtCore/QDebug>
#include <QtCore/QStack>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QDialog>

Execution::Execution(Analyse* pAnalyse) {
    m_analyse = pAnalyse;
    m_pileStructureControle = new QStack<Dictionnaire::typeLigne>();
    m_modifie = false;
}

Execution::~Execution() {
    delete m_pileStructureControle;
}

void Execution::lancer() {
    qDebug() << "Exécution commencée";

    execution();

    qDebug() << "Exécution terminée";
    emit terminee();
}

QString Execution::remplacementValeursVariables(QString pChaine) {
    pChaine = pChaine.trimmed();
    pChaine.replace("×", "*");
    pChaine.replace("÷", "/");
    for (int i = 0; i < m_analyse->getGlossaire()->getListeVariables().length(); i++) {
        QRegExp rx(".*(?:^|\\W)(" + m_analyse->getGlossaire()->getListeVariables().at(i) + ")(?:\\W|$).*");
        while (rx.exactMatch(pChaine))
            pChaine.replace(rx.pos(1), rx.cap(1).length(), m_analyse->getGlossaire()->getValeur(m_analyse->getGlossaire()->getListeVariables().at(i)));
    }

    MathExp* me = new MathExp();
    me->setExpression(pChaine);
    return QString::number(me->calcul());
}

bool Execution::evaluationCondition(QString pVal1, QString pOp, QString pVal2) {
    pVal1 = pVal1.trimmed();
    pOp = pOp.trimmed();
    pVal2 = pVal2.trimmed();
    qDebug() << "pVal1 : " << pVal1 << " - pOp : " << pOp << " - pVal2 : " << pVal2;

    ExpressionLogique* tmp = new ExpressionLogique();
    tmp->setExpression(pVal1 + pOp + pVal2);
    bool res = tmp->resultat();
    delete tmp;
    qDebug() << res;
    return res;
}

void Execution::execution(int pDebut, int pFin) {
    if (pFin == -1)
        pFin = m_analyse->getListeInstruction()->length();
    for (int i = pDebut; i < pFin; i++) {
        Instruction* inst = m_analyse->getListeInstruction()->at(i);
        if (inst->getTypeLigne() == Dictionnaire::Affectation) {
            m_analyse->getGlossaire()->setValeur(inst->getArgs()->at(1), remplacementValeursVariables(inst->getArgs()->at(2)));
        } else if (inst->getTypeLigne() == Dictionnaire::Afficher) {
            if (inst->getArgs()->at(1).trimmed().startsWith("\"")) {
                QString tmp = inst->getArgs()->at(1);
                tmp = tmp.remove(tmp.indexOf('"'), 1);
                tmp = tmp.remove(tmp.lastIndexOf('"'), 1);
                emit afficher(tmp);
            } else
                emit afficher(remplacementValeursVariables(inst->getArgs()->at(1)));
        } else if (inst->getTypeLigne() == Dictionnaire::Saisir) {
            m_analyse->emettreSaisie();
            if(m_modifie = true) {
                m_analyse->getGlossaire()->setValeur(inst->getArgs()->at(1), m_saisie);
            }
        } else if (inst->getTypeLigne() == Dictionnaire::Pour) {
            for (int j = remplacementValeursVariables(inst->getArgs()->at(2)).toInt(); j <= remplacementValeursVariables(inst->getArgs()->at(3)).toInt(); j++) {
                m_analyse->getGlossaire()->setValeur(inst->getArgs()->at(1), QString::number(j));
                execution(inst->getLigneDebut() + 1, inst->getLigneFin());
            }
            i = inst->getLigneFin();
        } else if (inst->getTypeLigne() == Dictionnaire::TantQue) {
            while (evaluationCondition(remplacementValeursVariables(inst->getArgs()->at(1)), inst->getArgs()->at(2), remplacementValeursVariables(inst->getArgs()->at(3))))
                execution(inst->getLigneDebut() + 1, inst->getLigneFin());
            i = inst->getLigneFin();
        } else if (inst->getTypeLigne() == Dictionnaire::Si) {
            qDebug() << "-- Si --";
            if (evaluationCondition(remplacementValeursVariables(inst->getArgs()->at(1)), inst->getArgs()->at(2), remplacementValeursVariables(inst->getArgs()->at(3)))) {
                if (inst->getLigneMilieu() >= 0)
                    execution(inst->getLigneDebut() + 1, inst->getLigneMilieu());
                else
                    execution(inst->getLigneDebut() + 1, inst->getLigneFin());
            } else {
                if (inst->getLigneMilieu() >= 0)
                    execution(inst->getLigneMilieu() + 1, inst->getLigneFin());
            }
            i = inst->getLigneFin();
        }
    }
}

void Execution::enregistrerSaisie(QString pSaisie) {
    m_saisie = pSaisie;
    m_modifie = true;
}
