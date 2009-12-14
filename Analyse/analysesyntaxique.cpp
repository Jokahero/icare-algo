#include "analysesyntaxique.h"
#include "analyse.h"
#include "glossaire.h"
#include "dictionnaire.h"

AnalyseSyntaxique::AnalyseSyntaxique(Analyse* pAnalyse) {
    m_analyse = pAnalyse;
}

void AnalyseSyntaxique::lancer(QFile* pFichier) {
    qDebug() << "Analyse syntaxique commencée.";
    lectureGlossaire(pFichier);
    lectureInstructions(pFichier);
    emit terminee();
    qDebug() << "Analyse syntaxique terminée.";
}

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
            m_analyse->setDebutAlgo(cptLigne);
        } else if (Dictionnaire::isFin(ligneAct)) {
            m_analyse->setFinAlgo(cptLigne);
        }
    }

    // Si il y a un glossaire :
    if (debutGlossaire > -1) {
        pFichier->seek(debutGlossaire);
        while (pFichier->pos() < finGlossaire) {
            ligneAct = pFichier->readLine().trimmed();
            if (rxVariable.exactMatch(ligneAct)) {
                QString type = rxVariable.cap(1);
                QString nomVar = rxVariable.cap(2);
                QString desc = rxVariable.cap(3);
                if (rxEntier.exactMatch(type)) {
                    m_analyse->getGlossaire()->ajoutEntier(nomVar, desc);
                } else if (rxReel.exactMatch(type)) {
                    m_analyse->getGlossaire()->ajoutReel(nomVar, desc);
                } else if (rxChaine.exactMatch(type) || rxCaractere.exactMatch(type)) {
                    m_analyse->getGlossaire()->ajoutChaine(nomVar, desc);
                }
            }
        }
    }

    pFichier->close();

    qDebug() << "Lecture du glossaire terminée.";
}


/*! \brief  Génère la liste des instructions de l'algo à stocker dans un tableau d'instruction
            Les lignes vides ne sont pas stockées.
            Si l'instruction est de type inconnu alors ERREUR. Sinon elle est stockée!
  \param pFichier Fichier à analyser.
  \todo Gestion des erreurs.
  */
void AnalyseSyntaxique::lectureInstructions(QFile* pFichier) {
    qDebug() << "Lecture des instructions commencée.";

    //ATTRIBUTS
    int debutAlgo = -1;                     //numero de la ligne DEBUT
    int finAlgo= -1;                        //numero de la ligne FIN
    int cptLigne;                           //nombre de ligne de l'algo
    Instruction* instructionAct;
    QString ligneAct;                       //Ligne: l'instruction actuelle (celle que l'on étudie à un moment)


    pFichier->open(QIODevice::ReadOnly | QIODevice::Text);


    //Reperer le numero de la ligne de DEBUT et la ligne de FIN
    while (!pFichier->atEnd() && finAlgo < 0) {
        ligneAct = pFichier->readLine().trimmed();
        if (Dictionnaire::isDebut(ligneAct))
            debutAlgo = pFichier->pos();
        else if (Dictionnaire::isFin(ligneAct))
            finAlgo = pFichier->pos();
    }

    //retourner à la position passée en paramètre
    pFichier->seek(debutAlgo);


    //LECTURE DE L'ALGO
    for (cptLigne = m_analyse->getDebutAlgo(); pFichier->pos() < finAlgo; cptLigne++) {
        ligneAct = pFichier->readLine().trimmed();      //trimmed: enlèbe espace au début et a la fin
        /*
            Si c'est une ligne vide, on ne la stocke pas
            Si ce n'est pas une ligne vide mais est de type TypeInconnu alors ERREUR
            Sinon Si ce n'est pas un commentaire ou une ligne vide, l'ajouter à la liste d'instructions
        */
        Dictionnaire::typeLigne typeLigneAct = Dictionnaire::getType(ligneAct);
        if (ligneAct != QString::null && typeLigneAct == Dictionnaire::TypeInconnu) {
            //erreur

        } else if (ligneAct != QString::null && typeLigneAct != Dictionnaire::Commentaire) {
            instructionAct = new Instruction(cptLigne, ligneAct, QString::null);
                //  CATEGORIE de l'instruction à voir si utile

            m_analyse->getListeInstruction()->append(instructionAct);
        }
    }

    pFichier->close();

    qDebug() << "Lecture des instructions terminée.";
}
