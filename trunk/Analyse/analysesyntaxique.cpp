#include "analysesyntaxique.h"

AnalyseSyntaxique::AnalyseSyntaxique(TextEdit* pTextEdit) {
    m_glossaire = new Glossaire();
    m_zoneTexte = pTextEdit;
}

void AnalyseSyntaxique::lancer() {
    qDebug() << "Analyse syntaxique commencée.";
    lectureGlossaire();
    emit terminee();
    qDebug() << "Analyse syntaxique terminée.";
}

void AnalyseSyntaxique::lectureGlossaire() {
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

    m_zoneTexte->retourDebut();

    // On cherche le début et la fin du glossaire
    while (!m_zoneTexte->finFichier() && finGlossaire < 0) {
        ligneAct = m_zoneTexte->lectureLigne();
        if (rxGlossaire.exactMatch(ligneAct))
            debutGlossaire = m_zoneTexte->numLigneActuelle();
        else if (rxDebut.exactMatch(ligneAct))
            finGlossaire = (m_zoneTexte->numLigneActuelle() - 1);
    }

    // Si il y a un glossaire :
    if (debutGlossaire > -1) {
        for (int i = debutGlossaire; i < finGlossaire; i++) {
            ligneAct = m_zoneTexte->lectureLigne(i);
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
    qDebug() << "Lecture du glossaire terminée.";
}

Glossaire* AnalyseSyntaxique::getGlossaire() {
    return m_glossaire;
}
