#include "analysesyntaxique.h"
#include "analyse.h"
#include "glossaire.h"

AnalyseSyntaxique::AnalyseSyntaxique(Analyse* pAnalyse) {
    m_analyse = pAnalyse;
}

void AnalyseSyntaxique::lancer(QFile* pFichier) {
    qDebug() << "Analyse syntaxique commencée.";    //permet d'afficher un message
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
    QRegExp rxGlossaire("^glossaire\\s*:?$");
    QRegExp rxDebut("^d[eé]but\\s*:?$");
    QRegExp rxVariable("^(entier|r[ée]el|cha[îi]ne|caract[eè]re)\\s+([a-zA-Z]+)\\s+((?:\\w*\\s*)*)$");
    QRegExp rxEntier("^entier$");
    QRegExp rxReel("^r[ée]el$");
    QRegExp rxChaine("^cha[îi]ne$");
    QRegExp rxCaractere("^caract[èe]re$");
    QRegExp rxFin("^fin$");

    rxGlossaire.setCaseSensitivity(Qt::CaseInsensitive);
    rxDebut.setCaseSensitivity(Qt::CaseInsensitive);
    rxVariable.setCaseSensitivity(Qt::CaseInsensitive);
    rxEntier.setCaseSensitivity(Qt::CaseInsensitive);
    rxReel.setCaseSensitivity(Qt::CaseInsensitive);
    rxChaine.setCaseSensitivity(Qt::CaseInsensitive);
    rxCaractere.setCaseSensitivity(Qt::CaseInsensitive);

    pFichier->open(QIODevice::ReadOnly | QIODevice::Text);

    for (cptLigne = 1; !pFichier->atEnd(); cptLigne++) {
        ligneAct = pFichier->readLine().trimmed();
        if (rxGlossaire.exactMatch(ligneAct)) {
            debutGlossaire = pFichier->pos();
            m_analyse->setDebutGlossaire(cptLigne);
        } else if (rxDebut.exactMatch(ligneAct)) {
            finGlossaire = pFichier->pos();
            m_analyse->setFinGlossaire(cptLigne);
            m_analyse->setDebutAlgo(cptLigne);
        } else if (rxFin.exactMatch(ligneAct)) {
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

void AnalyseSyntaxique::lectureInstructions(QFile* pFichier) {
    qDebug() << "Lecture des instructions commencée.";

    int debutAlgo = -1;
    int finAlgo= -1;
    int cptLigne;
    Instruction* instructionAct;
    QString ligneAct;
    QRegExp rxDebut("^d[eé]but\\s*:?$");
    QRegExp rxFin("^fin$");

    rxDebut.setCaseSensitivity(Qt::CaseInsensitive);
    rxFin.setCaseSensitivity(Qt::CaseInsensitive);

    pFichier->open(QIODevice::ReadOnly | QIODevice::Text);

    while (!pFichier->atEnd() && finAlgo < 0) {
        ligneAct = pFichier->readLine().trimmed();
        if (rxDebut.exactMatch(ligneAct))
            debutAlgo = pFichier->pos();
        else if (rxFin.exactMatch(ligneAct))
            finAlgo = pFichier->pos();
    }

    pFichier->seek(debutAlgo);
    for (cptLigne = m_analyse->getDebutAlgo(); pFichier->pos() < finAlgo; cptLigne++) {
        ligneAct = pFichier->readLine().trimmed();
        // Si ce n'est pas un commentaire ou une ligne vide, l'ajouter à la liste d'instructions
        instructionAct = new Instruction(cptLigne, ligneAct, QString::null);
        qDebug() << "nouvelle instruction ajoutée : " << instructionAct->getNumLigne() << " : " << instructionAct->getLigne();
        m_analyse->getListeInstruction()->append(instructionAct);
    }

    pFichier->close();

    qDebug() << "Lecture des instructions terminée.";
}
