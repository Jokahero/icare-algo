#include "dictionnaire.h"
#include "glossaire.h"
#include <QRegExp>

Dictionnaire::typeLigne Dictionnaire::getType(QString pLigne ){
if (isGlossaire(pLigne))
    return Dictionnaire::Glossaire;
else if (isDeclarationVariable(pLigne))
    return Dictionnaire::DeclarationVariable;
else if (isDebut(pLigne))
    return Dictionnaire::Debut;
else if (isFin(pLigne))
    return Dictionnaire::Fin;
else if (isCommentaire(pLigne))
    return Dictionnaire::Commentaire;
else
    return Dictionnaire::TypeInconnu;
}

//PARTIE GENERALE
/*! \brief Permet de savoir si le ligne est le début du Glossaire.

  Indique si la ligne est une ligne "Glossaire".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Glossaire", faux sinon.
*/
bool Dictionnaire::isGlossaire(QString pLigne) {
    QRegExp rx("^glossaire\\s?:?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}
/*! \brief Permet de savoir si le ligne est une déclaration de variable.

  Indique si la ligne est une ligne de déclaration de variables.

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est une ligne de déclaration de variables, faux sinon.
*/
bool Dictionnaire::isDeclarationVariable(QString pLigne) {
    QRegExp rx("^(entier|r[ée]el|cha[îi]ne|caract[eè]re|bool[ée]en)\\s+([a-z]+\\w*)\\s+((?:\\w*\\s*)*)$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}
/*! \brief Permet de savoir si le ligne est le début de l'algorithme.

  Indique si la ligne est une ligne "Debut".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Debut", faux sinon.
*/
bool Dictionnaire::isDebut(QString pLigne) {
    QRegExp rx("^d[eé]but\\s?:?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}
/*! \brief Permet de savoir si le ligne est la fin de l'algorithme.

  Indique si la ligne est une ligne "Fin".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Fin", faux sinon.
*/
bool Dictionnaire::isFin(QString pLigne) {
    QRegExp rx("^fin$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}
/*! \brief Permet de savoir si le ligne est un commentaire uniligne.

  Indique si la ligne est une ligne //(Commentaire).

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un //(Commentaire), faux sinon.
*/
bool Dictionnaire::isCommentaire(QString pLigne) {
    QRegExp rx("^//");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}

//FOR
/*! \brief Permet de savoir si le ligne est un "FinPour".

  Indique si la ligne est une ligne "FinPour".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "FinPour", faux sinon.
*/
bool Dictionnaire::isFinPour(QString pLigne) {
    QRegExp rx("^finpour$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}

//SWITCH
/*! \brief Permet de savoir si le ligne est un Default (Cas par défault de Selon).

  Indique si la ligne est une ligne "Default" (Cas par défault de Selon).

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Default" (Cas par défault de Selon), faux sinon.
*/
bool Dictionnaire::isDefault(QString pLigne) {
    QRegExp rx("^default\\s?:?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}
/*! \brief Permet de savoir si le ligne est un FinSelon.

  Indique si la ligne est une ligne "FinSelon".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "FinSelon", faux sinon.
*/
bool Dictionnaire::isFinSelon(QString pLigne) {
QRegExp rx("^finselon$");
rx.setCaseSensitivity(Qt::CaseInsensitive);
return rx.exactMatch(pLigne);
}

//DO..WHILE
/*! \brief Permet de savoir si le ligne est un "Repeter".

  Indique si la ligne est une ligne "Repeter".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Repeter", faux sinon.
*/
bool Dictionnaire::isRepeter(QString pLigne) {
QRegExp rx("^repeter$");
rx.setCaseSensitivity(Qt::CaseInsensitive);
return rx.exactMatch(pLigne);
}

//IF..ELSE..
/*! \brief Permet de savoir si le ligne est un "Si".

  Indique si la ligne est une ligne "Si".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Si", faux sinon.
*/
bool Dictionnaire::isSi(QString pLigne) {




    QRegExp rx("^si\\s" + expression + "+*$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}
/*! \brief Permet de savoir si le ligne est un "FinSi".

  Indique si la ligne est une ligne "FinSi".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "FinSi", faux sinon.
*/
bool Dictionnaire::isFinSi(QString pLigne) {
    QRegExp rx("^finsi$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}
/*! \brief Permet de savoir si le ligne est un "Sinon".

  Indique si la ligne est une ligne "Sinon".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Sinon", faux sinon.
*/
bool Dictionnaire::isSinon(QString pLigne) {
    QRegExp rx("^sinon$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}

//WHILE











//Expression réguliere de toute les variable séparé par un pipe
QString Dictionnaire::listePipeVariable()
{
    QString expression;
    QStringList listeVar = Glossaire::getListeVariables();
    while(!listeVar.empty())
    {
        expression += listeVar.first();
        expression += '|';
        listeVar.removeFirst();
    }
    return expression;

}


