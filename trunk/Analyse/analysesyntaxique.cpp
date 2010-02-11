#include "analysesyntaxique.h"
#include "glossaire.h"
#include "dictionnaire.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QRegExp>

AnalyseSyntaxique::AnalyseSyntaxique(Analyse* pAnalyse) {
    m_analyse = pAnalyse;
}

/*! \brief Lance successivement toutes les étapes de l'analyse syntaxique pour un fichier.

  \param pFichier Pointeur vers le fichier à analyser.
*/
void AnalyseSyntaxique::lancer(QFile* pFichier) {
    qDebug() << "Analyse syntaxique commencée.";
    lectureGlossaire(pFichier);
    lectureInstructions(pFichier);
    emit terminee();
    qDebug() << "Analyse syntaxique terminée.";
}

/*! \brief Lit le glossaire du fichier passé en paramètre.

  \param pFichier Pointeur vers le fichier à analyser.
*/
void AnalyseSyntaxique::lectureGlossaire(QFile* pFichier) {
    qDebug() << "Lecture du glossaire commencée.";

    int debutGlossaire = -1;
    int finGlossaire = -1;
    int cptLigne;
    QString ligneAct;
    QRegExp rxVariable("^(entier|r[ée]el|cha[îi]ne|caract[eè]re)\\s+([a-zA-Z]+)\\s+((?:\\w*\\s*)*)$");
    QRegExp rxEntier("^entier$");
    QRegExp rxReel("^r[ée]el$");
    QRegExp rxChaine("^cha[îi]ne$");
    QRegExp rxCaractere("^caract[èe]re$");

    rxVariable.setCaseSensitivity(Qt::CaseInsensitive);
    rxEntier.setCaseSensitivity(Qt::CaseInsensitive);
    rxReel.setCaseSensitivity(Qt::CaseInsensitive);
    rxChaine.setCaseSensitivity(Qt::CaseInsensitive);
    rxCaractere.setCaseSensitivity(Qt::CaseInsensitive);

    m_analyse->getGlossaire()->reinit();

    pFichier->open(QIODevice::ReadOnly | QIODevice::Text);

    //Reperer le numero de la ligne de DebutGlossaire et de FinGlossaire
    for (cptLigne = 1; !pFichier->atEnd(); cptLigne++) {
        ligneAct = pFichier->readLine().trimmed();      //enlever les espaces
        if (Dictionnaire::isGlossaire(ligneAct)) {
            debutGlossaire = pFichier->pos();           //recuperer l'endroit exact (au bit près) d'où on se trouve
            m_analyse->setDebutGlossaire(cptLigne);     //recuperer le numero de la ligne
        } else if (Dictionnaire::isDebut(ligneAct)) {
            finGlossaire = pFichier->pos();
            m_analyse->setFinGlossaire(cptLigne);
            m_analyse->setDebutAlgo(cptLigne + 1);
        } else if (Dictionnaire::isFin(ligneAct)) {
            m_analyse->setFinAlgo(cptLigne);
        }
    }

    // Si il y a un glossaire :
    if (debutGlossaire > -1) {
        pFichier->seek(debutGlossaire);
        for (cptLigne = m_analyse->getDebutGlossaire() + 1; pFichier->pos() < finGlossaire; cptLigne++) {
            ligneAct = pFichier->readLine().trimmed();
            if (rxVariable.exactMatch(ligneAct)) {
                QString type = rxVariable.cap(1);
                QString nomVar = rxVariable.cap(2);
                QString desc = rxVariable.cap(3).trimmed();
                if (rxEntier.exactMatch(type)) {
                    m_analyse->getGlossaire()->ajoutEntier(nomVar, desc, cptLigne);
                } else if (rxReel.exactMatch(type)) {
                    m_analyse->getGlossaire()->ajoutReel(nomVar, desc, cptLigne);
                } else if (rxChaine.exactMatch(type) || rxCaractere.exactMatch(type)) {
                    m_analyse->getGlossaire()->ajoutChaine(nomVar, desc, cptLigne);
                }
            }
        }
    }

    pFichier->close();

    qDebug() << "Lecture du glossaire terminée.";
}


/*! \brief  Génère la liste des instructions de l'algo à stocker dans une liste d'instructions.

  Les lignes vides ne sont pas stockées.
  Si l'instruction est de type inconnu alors le signal erreur(numéro de ligne) est émit. Sinon, elle est stockée.
  \param pFichier Fichier à analyser.
  \todo Renseigner la catégorie des instructions ajoutées.
  */
void AnalyseSyntaxique::lectureInstructions(QFile* pFichier) {
    qDebug() << "Lecture des instructions commencée.";

    int posPrec = -1;
    int debutAlgo = -1;       // Position de la ligne début.
    int finAlgo= -1;          // Position de la ligne fin.
    int cptLigne;             // Position de ligne de l'algo.
    QString ligneAct;         // Ligne actuelle (celle que l'on étudie à un moment).

    //Ouverture du fichier pour commencer la lecture
    pFichier->open(QIODevice::ReadOnly | QIODevice::Text);
    pFichier->seek(0);


    // Recherche du numéro de la ligne de début et de la ligne de fin
    // Tant qu'on est pas arrivé à la fin du fichier alors on recherche si la ligne lue est de type Début
    //   ou Fin
    while (!pFichier->atEnd() && finAlgo < 0) {
        ligneAct = pFichier->readLine().trimmed();
        if (Dictionnaire::isDebut(ligneAct))
            debutAlgo = posPrec;
        else if (Dictionnaire::isFin(ligneAct))
            finAlgo = pFichier->pos();
        posPrec = pFichier->pos();
    }

    // Retour au début de l'algo.
    if (debutAlgo > 0)
        pFichier->seek(debutAlgo);
    else
        pFichier->seek(0);

    m_analyse->getListeInstruction()->clear();
    // Lecture de l'algo.
    for (cptLigne = m_analyse->getDebutAlgo() - 1; pFichier->pos() < finAlgo; cptLigne++) {
        ligneAct = pFichier->readLine().trimmed();
        /*
            Si c'est une ligne vide, on ne la stocke pas
            Si ce n'est pas une ligne vide mais est de type TypeInconnu alors ERREUR
            Sinon Si ce n'est pas un commentaire ou une ligne vide, l'ajouter à la liste d'instructions
        */
        if (ligneAct != QString::null && ligneAct != "") {
            QStringList* params = new QStringList;
            Dictionnaire::typeLigne typeLigneAct = Dictionnaire::getType(ligneAct, params);
            if (typeLigneAct == Dictionnaire::TypeInconnu)
                emit erreur(Analyse::Syntaxe, cptLigne);
            else if (typeLigneAct != Dictionnaire::Commentaire)
                m_analyse->getListeInstruction()->append(new Instruction(cptLigne, ligneAct, typeLigneAct, params));
        }
    }

    pFichier->close();

    qDebug() << "Lecture des instructions terminée.";
}
