#include "execution.h"

#include "expressionlogique.h"
#include "glossaire.h"
#include "mathexp.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QEventLoop>
#include <QtCore/QStack>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QDialog>

#include <QtCore/QDebug>


/** \brief Constructeur.

  \param pAnalyse Instance d'analyse
*/
Execution::Execution(Analyse* pAnalyse) {
    m_analyse = pAnalyse;
    m_modifie = false;
}


/** \brief Lance l'exécution du dernier fichier analysé.

  \param pPasAPas Indique si l'exécution se déroule normalement ou en mode pas à pas
*/
void Execution::lancer(bool pPasAPas) {
    qDebug() << "Exécution commencée";

    m_stop = false;
    execution(pPasAPas);

    qDebug() << "Exécution terminée";
    emit terminee();
}


/** \brief Demande une interruption à la fin de l'interprétation de la ligne en cours.
*/
void Execution::stop() {
    m_stop = true;
}


/** \brief Remplace chaque occurence d'une variable par sa valeur.

  \param pChaine Chaîne où remplacer les variables
  \return Chaîne avec les valeurs
*/
QString Execution::remplacementValeursVariables(const QString& pChaine) {
    QString chaine = pChaine.trimmed();
    for (int i = 0; i < m_analyse->getGlossaire()->getListeVariables().length(); i++) {
        QRegExp rx(".*(?:^|\\W)(" + m_analyse->getGlossaire()->getListeVariables().at(i) + ")(?:\\W|$).*");
        while (rx.exactMatch(chaine))
            chaine.replace(rx.pos(1), rx.cap(1).length(), m_analyse->getGlossaire()->getValeur(m_analyse->getGlossaire()->getListeVariables().at(i)));
    }

    return chaine;
}


/** \brief Calcule le résultat de l'opération passée en paramètre.

  \param pChaine Opération à évaluer
  \param pNumLigne Numéro de la ligne de l'opération
  \return Résultat de l'opération
*/
QString Execution::calcul(const QString& pChaine, int pNumLigne) {
    QString chaine = pChaine.trimmed();
    chaine.replace("×", "*");
    chaine.replace("÷", "/");

    MathExp* me = new MathExp(pNumLigne);
    connect(me, SIGNAL(sigErreur(MathExp::erreur, int)), this, SIGNAL(erreurMathematique(MathExp::erreur, int)));
    me->setExpression(chaine);
    QString res = QString::number(me->calcul());
    delete me;
    return res;
}


/** \brief Évalue une condition logique.

  \param pCond Condition à évaluer
  \param pNumLigne Numéro de la ligne de la condition
  \return Résultat de la condition
*/
bool Execution::evaluationCondition(const QString& pCond, int pNumLigne) {
    QString cond = pCond.trimmed();

    ExpressionLogique* tmp = new ExpressionLogique(pNumLigne);
    connect(tmp, SIGNAL(sigErreur(ExpressionLogique::erreur, int)), this, SIGNAL(erreurLogique(ExpressionLogique::erreur, int)));
    connect(tmp, SIGNAL(sigErreurMath(MathExp::erreur, int)), this, SIGNAL(erreurMathematique(MathExp::erreur, int)));
    tmp->setExpression(cond);
    bool res = tmp->resultat();
    delete tmp;
    return res;
}


/** \brief Exécute tout ou une partie d'un algorithme.

  \param pPasAPas Indique si l'exécution doit se dérouler normalement ou en mode pas à pas
  \param pDebut Numéro d'instruction à laquelle doit commencer l'exécution
  \param pFin Numéro d'instruction à laquelle doit s'arrêter l'exécution. Si égal à -1, l'exécution s'arrête à la fin
*/
void Execution::execution(bool pPasAPas, int pDebut, int pFin) {
    if (pFin == -1 || pFin > m_analyse->getListeInstruction()->length())
        pFin = m_analyse->getListeInstruction()->length();

    for (int i = pDebut; i < pFin && !m_stop; i++) {
        Instruction* inst = m_analyse->getListeInstruction()->at(i);
        if (pPasAPas)
            emit changementLigne(inst->getNumLigne());
        if (inst->getTypeLigne() == Dictionnaire::Affectation) {
            // Affectation
            m_analyse->getGlossaire()->setValeur(inst->getArgs()->at(1), calcul(remplacementValeursVariables(inst->getArgs()->at(2)), inst->getNumLigne()));
        } else if (inst->getTypeLigne() == Dictionnaire::Afficher) {
            // Afficher
            if (inst->getArgs()->at(1).trimmed().startsWith("\"")) {
                QString tmp = inst->getArgs()->at(1);
                tmp = tmp.remove(tmp.indexOf('"'), 1);
                tmp = tmp.remove(tmp.lastIndexOf('"'), 1);
                emit afficher(tmp);
            } else
                emit afficher(calcul(remplacementValeursVariables(inst->getArgs()->at(1)), inst->getNumLigne()));
        } else if (inst->getTypeLigne() == Dictionnaire::Saisir) {
            // Saisir
            m_modifie = false;
            m_analyse->emettreSaisie();
            waitForSignal(m_analyse, SIGNAL(sigSaisie(QString)));
            while (!m_modifie);
            m_analyse->getGlossaire()->setValeur(inst->getArgs()->at(1), m_saisie);
        } else if (inst->getTypeLigne() == Dictionnaire::Pour) {
            // Pour
            for (int j = calcul(remplacementValeursVariables(inst->getArgs()->at(2)), inst->getNumLigne()).toInt(); !m_stop && j <= calcul(remplacementValeursVariables(inst->getArgs()->at(3)), inst->getNumLigne()).toInt(); j++) {
                m_analyse->getGlossaire()->setValeur(inst->getArgs()->at(1), QString::number(j));
                execution(pPasAPas, inst->getLigneDebut() + 1, inst->getLigneFin());
                j = calcul(remplacementValeursVariables(inst->getArgs()->at(1)), inst->getNumLigne()).toInt();
            }
            i = inst->getLigneFin();
        } else if (inst->getTypeLigne() == Dictionnaire::TantQue) {
            // Tant que
            while (!m_stop && evaluationCondition(remplacementValeursVariables(inst->getArgs()->at(1)), inst->getNumLigne()))
                execution(pPasAPas, inst->getLigneDebut() + 1, inst->getLigneFin());
            i = inst->getLigneFin();
        } else if (inst->getTypeLigne() == Dictionnaire::Repeter) {
            // Répéter
            Instruction* fin = m_analyse->getListeInstruction()->at(inst->getLigneFin());
            do {
                execution(pPasAPas, inst->getLigneDebut() + 1, inst->getLigneFin());
            } while (!m_stop && !evaluationCondition(remplacementValeursVariables(fin->getArgs()->at(1)), fin->getNumLigne()));
            i = inst->getLigneFin();
        } else if (inst->getTypeLigne() == Dictionnaire::Si) {
            // Si
            if (evaluationCondition(remplacementValeursVariables(inst->getArgs()->at(1)), inst->getNumLigne())) {
                if (inst->getLigneMilieu() >= 0)
                    execution(pPasAPas, inst->getLigneDebut() + 1, inst->getLigneMilieu());
                else
                    execution(pPasAPas, inst->getLigneDebut() + 1, inst->getLigneFin());
            } else {
                if (inst->getLigneMilieu() >= 0)
                    execution(pPasAPas, inst->getLigneMilieu() + 1, inst->getLigneFin());
            }
            i = inst->getLigneFin();
        }
        if (pPasAPas)
            waitForSignal(m_analyse, SIGNAL(execPas()));

        // On traîte la file d'events afin de ne pas freezer l'interface
        qApp->processEvents();
    }
}


/** \brief Modifie la valeur de la dernière saisie et la marque comme modifiée.

  \param pSaisie Chaîne saisie par l'utilisateur
*/
void Execution::enregistrerSaisie(const QString& pSaisie) {
    m_saisie = pSaisie;
    m_modifie = true;
}


/** \brief Boucle (non bloquante) durant tant qu'un signal n'a pas été émit par un objet.

  \param pObj Objet émetteur
  \param pSig Signal attendu
*/
void Execution::waitForSignal(QObject* pObj, const char* pSig) {
    QEventLoop loop;
    connect(pObj, pSig, &loop, SLOT(quit()));
    loop.exec();
}
