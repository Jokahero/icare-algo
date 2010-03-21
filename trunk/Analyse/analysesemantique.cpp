#include "analysesemantique.h"
#include "analyse.h"
#include "glossaire.h"


#include <QtCore/QCoreApplication>
#include <QtCore/QStack>
#include <QtCore/QStringList>


/** \brief Initialise les piles/listes.
*/
AnalyseSemantique::AnalyseSemantique(Analyse* pAnalyse) {
    m_analyse = pAnalyse;
    m_pileStructureControle = new QStack<Dictionnaire::typeLigne>;
    m_pilePosition = new QStack<int>;
    m_listeVariables = new QList<QString>;
}


/** \brief Destructeur.
*/
AnalyseSemantique::~AnalyseSemantique() {
    delete m_pileStructureControle;
    delete m_pilePosition;
    delete m_listeVariables;
}


/** \brief Lance les deux analyses l'une après l'autre.
*/
void AnalyseSemantique::lancer() {
    bool ret = true;

    if (!verifStruct())
        ret = false;

    if (!verifInitialisations())
        ret = false;

    emit terminee(ret);
}


/** \brief Vérifie l'imbrication de boucles/structures de contrôle.

  \return Vrai si l'analyse s'est bien passée, faux si il y a eu des erreurs.
*/
bool AnalyseSemantique::verifStruct() {
    bool ret = true;

    for (int i = 0; i < m_analyse->getListeInstruction()->length(); i++) {
        Dictionnaire::typeLigne type = m_analyse->getListeInstruction()->at(i)->getTypeLigne();
        if (type == Dictionnaire::Debut || type == Dictionnaire::Si || type == Dictionnaire::TantQue || type == Dictionnaire::Pour || type == Dictionnaire::Repeter) {
            m_pileStructureControle->push(type);
            m_pilePosition->push(i);
        }
        
        else if (type == Dictionnaire::Fin) {
            if (m_pileStructureControle->top() == Dictionnaire::Debut)
                pop(i);
            else {
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());
                ret = false;
            }
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
            } else {
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());
                ret = false;
            }
        } else if (type == Dictionnaire::Sinon) {
            if (m_pileStructureControle->top() != Dictionnaire::Si) {
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());
                ret = false;
            } else {
                m_analyse->getListeInstruction()->at(m_pilePosition->top())->setLigneMilieu(i);
                m_analyse->getListeInstruction()->at(i)->setLigneDebut(m_pilePosition->top());
                m_analyse->getListeInstruction()->at(i)->setLigneMilieu(i);
            }
        } else if (type == Dictionnaire::FinTantQue) {
            if (m_pileStructureControle->top() == Dictionnaire::TantQue)
                pop(i);
            else {
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());
                ret = false;
            }
        } else if (type == Dictionnaire::FinPour) {
            if (m_pileStructureControle->top() == Dictionnaire::Pour)
                pop(i);
            else {
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());
                ret = false;
            }
        } else if (type == Dictionnaire::Jusqua) {
            if (m_pileStructureControle->top() == Dictionnaire::Repeter)
                pop(i);
            else {
                emit erreur(Analyse::Struct, m_analyse->getListeInstruction()->at(i)->getNumLigne());
                ret = false;
            }
        }

        // On traîte la file d'events afin de ne pas freezer l'interface
        qApp->processEvents();
    }

    // Vidage de la pile pour la prochaine analyse
    if (!m_pileStructureControle->empty())
        m_pileStructureControle->resize(0);

    return ret;
}


/** \brief Vérifie que toutes les variables utilisées soient bien initialisées.

  \return Vrai si l'analyse s'est bien passée, faux si il y a eu des erreurs.
*/
bool AnalyseSemantique::verifInitialisations() {
    bool ret = true;

    for (int i = 0; i < m_analyse->getListeInstruction()->length(); i++) {
        Instruction* inst = m_analyse->getListeInstruction()->at(i);
        if (inst->getTypeLigne() == Dictionnaire::Affectation || inst->getTypeLigne() == Dictionnaire::Saisir || inst->getTypeLigne() == Dictionnaire::Pour)
            m_listeVariables->append(inst->getArgs()->at(1));

        // Suppression des chaînes
        QString ligne = inst->getLigne();
        while (ligne.contains("\"")) {
            int pos = ligne.indexOf("\"");
            ligne.replace(pos, 1, " ");
            int pos2 = ligne.indexOf("\"");
            ligne.replace(pos, (pos2 - pos), "");
        }

        for (int j = 0; j < m_analyse->getGlossaire()->getListeVariables().length(); j++)
            if (ligne.contains(QRegExp(".*(?:^|\\W)" + m_analyse->getGlossaire()->getListeVariables().at(j) + "(?:\\W|$).*")))
                if (!m_listeVariables->contains(m_analyse->getGlossaire()->getListeVariables().at(j))) {
                    emit erreur(Analyse::VariableNonInitialisee, inst->getNumLigne());
                    ret = false;
                }

        // On traîte la file d'events afin de ne pas freezer l'interface
        qApp->processEvents();
    }

    // Vidage de la liste pour la prochaine analyse
    if (!m_listeVariables->empty())
        m_listeVariables->clear();

    return ret;
}


/** \brief Utilisée lors de la première analyse, permet d'enlever des deux piles les dernières valeurs et d'initialiser correctement les numéros de lignes correspondants.

  \param i Numéro de ligne actuel
*/
void AnalyseSemantique::pop(int i) {
    m_pileStructureControle->pop();
    int tmp = m_pilePosition->top();
    m_pilePosition->pop();
    m_analyse->getListeInstruction()->at(tmp)->setLigneDebut(tmp);
    m_analyse->getListeInstruction()->at(tmp)->setLigneFin(i);
    m_analyse->getListeInstruction()->at(i)->setLigneDebut(tmp);
    m_analyse->getListeInstruction()->at(i)->setLigneFin(i);
}
