#include "execution.h"
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
    for (int i = 0; i < m_analyse->getGlossaire()->getListeVariables().length(); i++)
        pChaine.replace(QRegExp("(^|[\\(|\\+|\\*|\\/|\\-|\\)|\\s]+)("+ m_analyse->getGlossaire()->getListeVariables().at(i) +")([\\(|\\+|\\*|\\/|\\-|\\)|\\s]+|$)"),m_analyse->getGlossaire()->getValeur(m_analyse->getGlossaire()->getListeVariables().at(i)));
    pChaine.replace("×", "*");
    pChaine.replace("÷", "/");

    MathExp* me = new MathExp();
    me->setExpression(pChaine);

    return QString::number(me->calcul());
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
        } else if (inst->getTypeLigne() == Dictionnaire::Pour) {
            for (int j = remplacementValeursVariables(inst->getArgs()->at(2)).toInt(); j < remplacementValeursVariables(inst->getArgs()->at(3)).toInt(); j++) {
                m_analyse->getGlossaire()->setValeur(inst->getArgs()->at(1), QString::number(j));
                execution(inst->getLigneDebut() + 1, inst->getLigneFin());
            }
            i = inst->getLigneFin();
        }
    }
}
