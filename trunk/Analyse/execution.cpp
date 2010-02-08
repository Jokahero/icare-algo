#include "execution.h"
#include "glossaire.h"
#include "mathexp.h"

#include <QtCore/QDebug>
#include <QtCore/QStack>
#include <QtCore/QString>
#include <QtCore/QStringList>

Execution::Execution(Analyse* pAnalyse) {
    m_analyse = pAnalyse;
    m_pileStructureControle = new QStack<Dictionnaire::typeLigne>();
}

void Execution::lancer() {
    qDebug() << "Exécution commencée";

    for (int i = 0; i < m_analyse->getListeInstruction()->length(); i++) {
        Instruction* inst = m_analyse->getListeInstruction()->at(i);
        if (inst->getTypeLigne() == Dictionnaire::Affectation) {
            m_analyse->getGlossaire()->setValeur(inst->getArgs()->at(1), remplacementValeursVariables(inst->getArgs()->at(2)));
        }
    }

    qDebug() << "Exécution terminée";
    emit terminee();
}

// TODO: Vérifier que la variable soit bien la même (production, i : product0on)
QString Execution::remplacementValeursVariables(QString pChaine) {
    for (int i = 0; i < m_analyse->getGlossaire()->getListeVariables().length(); i++)
        pChaine.replace(m_analyse->getGlossaire()->getListeVariables().at(i), m_analyse->getGlossaire()->getValeur(m_analyse->getGlossaire()->getListeVariables().at(i)), Qt::CaseInsensitive);
    pChaine.replace("×", "*");
    pChaine.replace("÷", "/");

    // Faire appel au module d'expressions mathématiques ici
    MathExp* me = new MathExp();
    me->setExpression(pChaine);

    return QString::number(me->calcul());

}
