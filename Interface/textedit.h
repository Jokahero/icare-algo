#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QtGui>
/*! \brief Zone de texte permettant d'afficher et de modifier le contenu du fichier
  */
class TextEdit : public QTextEdit
{
public:
    TextEdit();

    QString lectureLigne(int pNumLigne);
    QString lectureLigne();
    bool finFichier(int pNumLigne);
    bool finFichier();

private:
    int m_derniereLigneLue;
};

#endif // TEXTEDIT_H
