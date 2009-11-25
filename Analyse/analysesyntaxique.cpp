#include "analysesyntaxique.h"

AnalyseSyntaxique::AnalyseSyntaxique() {
    m_glossaire = new Glossaire();
}

void AnalyseSyntaxique::lancer(QFile* pFichier) {
    qDebug() << "Analyse syntaxique commencée.";
    lectureGlossaire(pFichier);
    emit terminee();
    qDebug() << "Analyse syntaxique terminée.";
}

void AnalyseSyntaxique::lectureGlossaire(QFile* pFichier) {
    qDebug() << "Lecture du glossaire commencée.";

    int debutGlossaire = -1;
    int finGlossaire = -1;
    QString ligneAct;
    QRegExp rxGlossaire("^glossaire\\s*:?$");
    QRegExp rxDebut("^d[eé]but\\s*:?$");
    QRegExp rxVariable("^(entier|double|cha[îi]ne|caract[eè]re)\\s+([a-zA-Z]+)\\s+((?:\\w*\\s*)*)$");
    QRegExp rxEntier("^entier$");
    QRegExp rxDouble("^double$");
    QRegExp rxChaine("^cha[îi]ne$");
    QRegExp rxCaractere("^caract[èe]re$");

    rxGlossaire.setCaseSensitivity(Qt::CaseInsensitive);
    rxDebut.setCaseSensitivity(Qt::CaseInsensitive);
    rxVariable.setCaseSensitivity(Qt::CaseInsensitive);
    rxEntier.setCaseSensitivity(Qt::CaseInsensitive);
    rxDouble.setCaseSensitivity(Qt::CaseInsensitive);
    rxChaine.setCaseSensitivity(Qt::CaseInsensitive);
    rxCaractere.setCaseSensitivity(Qt::CaseInsensitive);

    pFichier->open(QIODevice::ReadOnly | QIODevice::Text);

    while (!pFichier->atEnd() && finGlossaire < 0) {
        ligneAct = pFichier->readLine().trimmed();
        if (rxGlossaire.exactMatch(ligneAct))
            debutGlossaire = pFichier->pos();
        else if (rxDebut.exactMatch(ligneAct))
            finGlossaire = pFichier->pos();
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
                    m_glossaire->ajoutEntier(nomVar, desc);
                } else if (rxDouble.exactMatch(type)) {
                    m_glossaire->ajoutDouble(nomVar, desc);
                } else if (rxChaine.exactMatch(type) || rxCaractere.exactMatch(type)) {
                    m_glossaire->ajoutChaine(nomVar, desc);
                }
            }
        }
    }

    pFichier->close();

    qDebug() << "Lecture du glossaire terminée.";
}

Glossaire* AnalyseSyntaxique::getGlossaire() {
    return m_glossaire;
}
