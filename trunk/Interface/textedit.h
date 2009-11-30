#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QtGui>
#include "coloration.h"

/*! \brief Zone de texte permettant d'afficher et de modifier le contenu du fichier
*/
class TextEdit : public QTextEdit {
    Q_OBJECT
public:
    TextEdit();

    QString lectureLigne(int pNumLigne);
    QString lectureLigne();
    bool finFichier(int pNumLigne);
    bool finFichier();
    void retourDebut();
    int numLigneActuelle();

private:
    int m_derniereLigneLue;
    bool m_texteModifie;
    QStringList m_listeLignes;
    Coloration *m_color;

private slots:
    void texteModifie();
};

#endif // TEXTEDIT_H
