#include "dictionnaire.h"
#include "glossaire.h"

#include <QtCore/QRegExp>
#include <QtCore/QString>
#include <QtCore/QStringList>

Dictionnaire::typeLigne Dictionnaire::getType(QString pLigne ){
    //-----PARTIE GENERALE
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
    else if (isAffectation(pLigne))
        return Dictionnaire::Affectation;
    //-----IF..ELSE..
    else if (isSi(pLigne))
        return Dictionnaire::Si;
    else if (isFinSi(pLigne))
        return Dictionnaire::FinSi;
    else if (isSinon(pLigne))
        return Dictionnaire::Sinon;
    //-----SWITCH
    else if (isSelon(pLigne))
        return Dictionnaire::Selon;
    else if (isCas(pLigne))
        return Dictionnaire::Cas;
    else if (isSelon(pLigne))
        return Dictionnaire::Default;
    else if (isFinSelon(pLigne))
        return Dictionnaire::FinSelon;
    //-----FOR
    else if (isPour(pLigne))
        return Dictionnaire::Pour;
    else if (isFinPour(pLigne))
        return Dictionnaire::FinPour;
    //-----DO..WHILE
    else if (isRepeter(pLigne))
        return Dictionnaire::Repeter;
    else if (isJusqua(pLigne))
        return Dictionnaire::Jusqua;
    //-----WHILE
    else if (isTantQue(pLigne))
        return Dictionnaire::TantQue;
    else if (isFinTantQue(pLigne))
        return Dictionnaire::FinTantQue;



    else
        return Dictionnaire::TypeInconnu;
}

//-----PARTIE GENERALE
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
    QRegExp rx("^//*$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}
/*! \brief Permet de savoir si le ligne est une affectation.

  Indique si la ligne est une ligne "expression <- expression".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est une affectation, faux sinon.
*/
bool Dictionnaire::isAffectation(QString pLigne) {
    QString  expression = listePipeVariable();
    QRegExp rx("^" + expression + "\\s*(:?<-|←)\\s*(" + expression + "|[0-9]+(\\.[0-9]+)?)+$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}








//-----IF..ELSE..
/*! \brief Permet de savoir si le ligne est un "Si".

  Indique si la ligne est une ligne "Si".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Si", faux sinon.
*/
bool Dictionnaire::isSi(QString pLigne) {
    //récupération de toute les variable utilisateur
    QString  expression = listePipeVariable();
    QRegExp rx("^si\\s(" + expression + "|[0-9]+)(≤|≥|≠|=|>|>=|<|<=|!=)(" + expression + "|[0-9]+)\\salors$");
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
//-----SWITCH
/*! \brief Permet de savoir si le ligne est un Selon.

  Indique si la ligne est une ligne "Selon".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Selon" , faux sinon.
*/
bool Dictionnaire::isSelon(QString pLigne) {
    QString expression = listePipeVariable();
    QRegExp rx("^selon\\s?\\(?(" + expression + ")\\)?:?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}
/*! \brief Permet de savoir si le ligne est un Cas(Differents choix du selon).

  Indique si la ligne est une ligne "Cas"(Differents choix du selon).

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Cas" , faux sinon.
*/
bool Dictionnaire::isCas(QString pLigne) {
    QString expression = listePipeVariable();
    QRegExp rx("^cas\\s?(" + expression + "|[0-9]+)\\s:?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}
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
//-----FOR
/*! \brief Permet de savoir si le ligne est un "Pour".

  Indique si la ligne est une ligne "Pour".
  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Pour", faux sinon.
*/
bool Dictionnaire::isPour(QString pLigne) {
    QString expression = listePipeVariable();
    QRegExp rx("^pour\\s("+expression+")\\sde\\s(" + expression + "|[0-9]+)[àa](" + expression + "|[0-9]+)(\\[pas\\sde\\s(" + expression + "|[0-9]+)\\])?\\sfaire$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}
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
//-----DO..WHILE
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
/*! \brief Permet de savoir si le ligne est un "Jusqu'a".

  Indique si la ligne est une ligne "Jusqu'a".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Jusqua", faux sinon.
*/
bool Dictionnaire::isJusqua(QString pLigne) {
    QString expression = listePipeVariable();
    QRegExp rx("^jusqu[\\s']?[àa]\\s(" + expression + "|[0-9]+)$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}
//WHILE
/*! \brief Permet de savoir si le ligne est un "TantQue".

  Indique si la ligne est une ligne "TantQue".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "TantQue", faux sinon.
*/
bool Dictionnaire::isTantQue(QString pLigne) {
    QString expression = listePipeVariable();
    QRegExp rx("^tantque\\s(" + expression + "|[0-9]+)(≤|≥|≠|=|>|>=|<|<=|!=)(" + expression + "|[0-9]+)$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}
/*! \brief Permet de savoir si le ligne est un "FinTantQue".

  Indique si la ligne est une ligne "FinTantQue".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "FinTantQue", faux sinon.
*/
bool Dictionnaire::isFinTantQue(QString pLigne) {
    QRegExp rx("^fintantque$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    return rx.exactMatch(pLigne);
}


//Expression réguliere de toute les variable séparé par un pipe
/*! \brief Permet de récupéré les variables du glossaire pour les transformé en chaine de caractère séparé d'un pipe

  Transformation de la liste de variable du gloassaire en : var1|var2|var3|...|varx

  \return String expression
*/
QString Dictionnaire::listePipeVariable()
{
    QString expression = "(";
    QStringList listeVar = Analyse::getInstance()->getGlossaire()->getListeVariables();
    if (!listeVar.empty()) {
        expression += listeVar.first();
        listeVar.removeFirst();
        while(!listeVar.empty()) {
            expression += '|';
            expression += listeVar.first();
            listeVar.removeFirst();
        }
    }
    expression += ")";
    return expression;
}
