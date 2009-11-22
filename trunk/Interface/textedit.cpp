#include "textedit.h"

TextEdit::TextEdit() {
    m_derniereLigneLue = 0;
}

/*! \brief Retourne le contenu de la ligne pNumLigne.

  Si la ligne n'existe pas (pas autant de lignes dans le fichier), retourne une chaîne vide.
  \param pNumLigne Numéro de la ligne à lire.
  \return Contenu de la ligne.
*/
QString TextEdit::lectureLigne(int pNumLigne) {
    if (pNumLigne > 0)
        m_derniereLigneLue = pNumLigne;
    else
        m_derniereLigneLue = 1;

    QStringList liste = toPlainText().split('\n');
    if (liste.size() >= (m_derniereLigneLue - 1))
        return liste.at(m_derniereLigneLue - 1);
    else
        return QString::null;
}

/*! \brief Retourne le contenu de la ligne suivant la dernière lue.

  Si la ligne n'existe pas (pas autant de lignes dans le fichier), retourne une chaîne vide.
  \return Contenu de la ligne.
*/
QString TextEdit::lectureLigne() {
    return lectureLigne(m_derniereLigneLue + 1);
}

/*! \brief Indique si la fin du fichier est atteinte en lisant la ligne pNumLigne.

  \param pNumLigne Numéro de la ligne à lire.
  \return Vrai si la fin du fichier est atteinte, faux sinon.
*/
bool TextEdit::finFichier(int pNumLigne) {
    if (toPlainText().split('\n').size() > (pNumLigne + 1))
        return false;
    else
        return true;
}

/*! \brief Indique si la fin du fichier a été atteinte lors de la dernière lecture.

  \return Vrai si la fin du fichier est atteinte, faux sinon.
*/
bool TextEdit::finFichier() {
    return finFichier(m_derniereLigneLue);
}
