#include "execution.h"

#include "expressionlogique.h"
#include "glossaire.h"
#include "mathexp.h"

#include <QtCore/QDebug>
#include <QtCore/QStack>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QDialog>
#include <QtCore/QEventLoop>

Execution::Execution(Analyse* pAnalyse) {
    m_analyse = pAnalyse;
    m_pileStructureControle = new QStack<Dictionnaire::typeLigne>();
    m_modifie = false;
}

Execution::~Execution() {
    delete m_pileStructureControle;
}

void Execution::lancer(bool pPasAPas) {
    qDebug() << "Exécution commencée";

    m_stop = false;
    execution(pPasAPas);

    qDebug() << "Exécution terminée";
    emit terminee();
}

void Execution::pas() {
    // TODO : Changement de ligne active sur l'interface
}

void Execution::stop() {
    m_stop = true;
}

QString Execution::remplacementValeursVariables(QString pChaine, int pNumLigne) {
    pChaine = pChaine.trimmed();
    pChaine.replace("×", "*");
    pChaine.replace("÷", "/");
    for (int i = 0; i < m_analyse->getGlossaire()->getListeVariables().length(); i++) {
        QRegExp rx(".*(?:^|\\W)(" + m_analyse->getGlossaire()->getListeVariables().at(i) + ")(?:\\W|$).*");
        while (rx.exactMatch(pChaine))
            pChaine.replace(rx.pos(1), rx.cap(1).length(), m_analyse->getGlossaire()->getValeur(m_analyse->getGlossaire()->getListeVariables().at(i)));
    }

    MathExp* me = new MathExp(pNumLigne);
    connect(me, SIGNAL(sigErreur(MathExp::erreur, int)), this, SIGNAL(erreurMathematique(MathExp::erreur, int)));
    me->setExpression(pChaine);
    QString res = QString::number(me->calcul());
    delete me;
    return res;
}

bool Execution::evaluationCondition(QString pVal1, QString pOp, QString pVal2, int pNumLigne) {
    pVal1 = pVal1.trimmed();
    pOp = pOp.trimmed();
    pVal2 = pVal2.trimmed();

    ExpressionLogique* tmp = new ExpressionLogique(pNumLigne);
    connect(tmp, SIGNAL(sigErreur(ExpressionLogique::erreur, int)), this, SIGNAL(erreurLogique(ExpressionLogique::erreur, int)));
    connect(tmp, SIGNAL(sigErreurMath(MathExp::erreur, int)), this, SIGNAL(erreurMathematique(MathExp::erreur, int)));
    tmp->setExpression(pVal1 + pOp + pVal2);
    bool res = tmp->resultat();
    delete tmp;
    return res;
}

void Execution::execution(bool pPasAPas, int pDebut, int pFin) {
    if (pFin == -1)
        pFin = m_analyse->getListeInstruction()->length();
    for (int i = pDebut; i < pFin && !m_stop; i++) {
        Instruction* inst = m_analyse->getListeInstruction()->at(i);
        if (inst->getTypeLigne() == Dictionnaire::Affectation) {
            m_analyse->getGlossaire()->setValeur(inst->getArgs()->at(1), remplacementValeursVariables(inst->getArgs()->at(2), inst->getNumLigne()));
        } else if (inst->getTypeLigne() == Dictionnaire::Afficher) {
            if (inst->getArgs()->at(1).trimmed().startsWith("\"")) {
                QString tmp = inst->getArgs()->at(1);
                tmp = tmp.remove(tmp.indexOf('"'), 1);
                tmp = tmp.remove(tmp.lastIndexOf('"'), 1);
                emit afficher(tmp);
            } else
                emit afficher(remplacementValeursVariables(inst->getArgs()->at(1), inst->getNumLigne()));
        } else if (inst->getTypeLigne() == Dictionnaire::Saisir) {
            m_modifie = false;
            m_analyse->emettreSaisie();
            waitForSignal(m_analyse, SIGNAL(sigSaisie(QString)));
            while (!m_modifie);
            m_analyse->getGlossaire()->setValeur(inst->getArgs()->at(1), m_saisie);
        } else if (inst->getTypeLigne() == Dictionnaire::Pour) {
            for (int j = remplacementValeursVariables(inst->getArgs()->at(2), inst->getNumLigne()).toInt(); j <= remplacementValeursVariables(inst->getArgs()->at(3), inst->getNumLigne()).toInt(); j++) {
                m_analyse->getGlossaire()->setValeur(inst->getArgs()->at(1), QString::number(j));
                execution(pPasAPas, inst->getLigneDebut() + 1, inst->getLigneFin());
            }
            i = inst->getLigneFin();
        } else if (inst->getTypeLigne() == Dictionnaire::TantQue) {
            while (evaluationCondition(remplacementValeursVariables(inst->getArgs()->at(1), inst->getNumLigne()), inst->getArgs()->at(2), remplacementValeursVariables(inst->getArgs()->at(3), inst->getNumLigne()), inst->getNumLigne()))
                execution(pPasAPas, inst->getLigneDebut() + 1, inst->getLigneFin());
            i = inst->getLigneFin();
        } else if (inst->getTypeLigne() == Dictionnaire::Si) {
            if (evaluationCondition(remplacementValeursVariables(inst->getArgs()->at(1), inst->getNumLigne()), inst->getArgs()->at(2), remplacementValeursVariables(inst->getArgs()->at(3), inst->getNumLigne()), inst->getNumLigne())) {
                if (inst->getLigneMilieu() >= 0)
                    execution(pPasAPas, inst->getLigneDebut() + 1, inst->getLigneMilieu());
                else
                    execution(pPasAPas, inst->getLigneDebut() + 1, inst->getLigneFin());
            } else {
                if (inst->getLigneMilieu() >= 0)
                    execution(inst->getLigneMilieu() + 1, inst->getLigneFin());
            }
            i = inst->getLigneFin();
        }
        if (pPasAPas)
            waitForSignal(m_analyse, SIGNAL(execPas()));
    }
}

void Execution::enregistrerSaisie(QString pSaisie) {
    m_saisie = pSaisie;
    m_modifie = true;
}

void Execution::waitForSignal(QObject* pObj, const char* pSig) {
    QEventLoop loop;
    connect(pObj, pSig, &loop, SLOT(quit()));
    loop.exec();
}
