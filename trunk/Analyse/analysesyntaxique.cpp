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

    m_zoneTexte->retourDebut();

    // On cherche le début et la fin du glossaire
    while (!m_zoneTexte->finFichier()) {
        ligneAct = m_zoneTexte->lectureLigne().toLower();
        // On récupère uniquement le premier mot :
        ligneAct = ligneAct.left(ligneAct.indexOf(' ')).replace(":", "");

        if (ligneAct == "glossaire")
            debutGlossaire = m_zoneTexte->numLigneActuelle();
        else if (ligneAct == "debut" || ligneAct == "début")
            finGlossaire = (m_zoneTexte->numLigneActuelle() - 1);
    }

    // Si il y a un glossaire :
    if (debutGlossaire > -1) {
        for (int i = debutGlossaire; i < finGlossaire; i++) {
            ligneAct = m_zoneTexte->lectureLigne(i).simplified();
            qDebug() << "ligneAct : " << ligneAct;
            QString type = ligneAct.left(ligneAct.indexOf(' ')).toLower();
            if (type == "entier" || type == "double" || type == "chaine" || type == "chaîne" || type == "caractere" || type == "caractère") {
                QString nomVar = ligneAct.right(ligneAct.size() - type.size() - 1);
                QString desc = nomVar.right(nomVar.size() - type.size() - 3);
                nomVar = nomVar.left(nomVar.indexOf(' '));
                if (type == "entier") {
                    m_glossaire->ajoutEntier(nomVar, desc);
                } else if (type == "double") {
                    m_glossaire->ajoutDouble(nomVar, desc);
                } else if (type == "chaine" || type == "chaîne" || type == "caractere" || type == "caractère") {
                    m_glossaire->ajoutChaine(nomVar, desc);
                }
            }
        }
    }
    qDebug() << "Lecture du glossaire terminée.";
}
