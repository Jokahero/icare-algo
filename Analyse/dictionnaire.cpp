#include "dictionnaire.h"
#include "glossaire.h"

#include <QtCore/QRegExp>
#include <QtCore/QString>
#include <QtCore/QStringList>

Dictionnaire::typeLigne Dictionnaire::getType(QString pLigne, QStringList* pListeArgs) {
    //-----PARTIE GENERALE
    if (isGlossaire(pLigne, pListeArgs))
        return Dictionnaire::Glossaire;
    else if (isDeclarationVariable(pLigne, pListeArgs))
        return Dictionnaire::DeclarationVariable;
    else if (isDebut(pLigne, pListeArgs))
        return Dictionnaire::Debut;
    else if (isFin(pLigne, pListeArgs))
        return Dictionnaire::Fin;
    else if (isCommentaire(pLigne, pListeArgs))
        return Dictionnaire::Commentaire;
    else if (isAffectation(pLigne, pListeArgs))
        return Dictionnaire::Affectation;
    //-----IF..ELSE..
    else if (isSi(pLigne, pListeArgs))
        return Dictionnaire::Si;
    else if (isFinSi(pLigne, pListeArgs))
        return Dictionnaire::FinSi;
    else if (isSinon(pLigne, pListeArgs))
        return Dictionnaire::Sinon;
    //-----SWITCH
    else if (isSelon(pLigne, pListeArgs))
        return Dictionnaire::Selon;
    else if (isCas(pLigne, pListeArgs))
        return Dictionnaire::Cas;
    else if (isSelon(pLigne, pListeArgs))
        return Dictionnaire::Default;
    else if (isFinSelon(pLigne, pListeArgs))
        return Dictionnaire::FinSelon;
    //-----FOR
    else if (isPour(pLigne, pListeArgs))
        return Dictionnaire::Pour;
    else if (isFinPour(pLigne, pListeArgs))
        return Dictionnaire::FinPour;
    //-----DO..WHILE
    else if (isRepeter(pLigne, pListeArgs))
        return Dictionnaire::Repeter;
    else if (isJusqua(pLigne, pListeArgs))
        return Dictionnaire::Jusqua;
    //-----WHILE
    else if (isTantQue(pLigne, pListeArgs))
        return Dictionnaire::TantQue;
    else if (isFinTantQue(pLigne, pListeArgs))
        return Dictionnaire::FinTantQue;

    else if (isAfficher(pLigne, pListeArgs))
        return Dictionnaire::Afficher;
    else if (isSaisir(pLigne, pListeArgs))
        return Dictionnaire::Saisir;
    else if (isImprimer(pLigne, pListeArgs))
        return Dictionnaire::Imprimer;


    else
        return Dictionnaire::TypeInconnu;
}

//-----PARTIE GENERALE
/*! \brief Permet de savoir si le ligne est le début du Glossaire.

  Indique si la ligne est une ligne "Glossaire".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Glossaire", faux sinon.
*/
bool Dictionnaire::isGlossaire(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^glossaire\\s?:?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    return rx.exactMatch(pLigne);
}
/*! \brief Permet de savoir si le ligne est une déclaration de variable.

  Indique si la ligne est une ligne de déclaration de variables.

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est une ligne de déclaration de variables, faux sinon.
*/
bool Dictionnaire::isDeclarationVariable(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^(entier|r[ée]el|cha[îi]ne|caract[eè]re|bool[ée]en)\\s+([a-z]+\\w*)\\s+((?:\\w*\\s*)*)$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    if (rx.exactMatch(pLigne)) {
        if (pListeArgs)
            *pListeArgs = rx.capturedTexts();
        return true;
    } else
        return false;
}
/*! \brief Permet de savoir si le ligne est le début de l'algorithme.

  Indique si la ligne est une ligne "Debut".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Debut", faux sinon.
*/
bool Dictionnaire::isDebut(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^d[eé]but\\s?:?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    return rx.exactMatch(pLigne);
}
/*! \brief Permet de savoir si le ligne est la fin de l'algorithme.

  Indique si la ligne est une ligne "Fin".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Fin", faux sinon.
*/
bool Dictionnaire::isFin(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^fin$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    return rx.exactMatch(pLigne);
}
/*! \brief Permet de savoir si le ligne est un commentaire uniligne.

  Indique si la ligne est une ligne //(Commentaire).

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un //(Commentaire), faux sinon.
*/
bool Dictionnaire::isCommentaire(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^//.*$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    return rx.exactMatch(pLigne);
}
/*! \brief Permet de savoir si le ligne est une affectation.

  Indique si la ligne est une ligne "expression <- expression".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est une affectation, faux sinon.
*/
bool Dictionnaire::isAffectation(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^(" + listePipeVariable() + ")\\s*(?:<-|←)\\s*(" + listeQuantites() + ")$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    if (rx.exactMatch(pLigne)) {
        if (pListeArgs)
            *pListeArgs = rx.capturedTexts();
        return true;
    } else
        return false;
}








//-----IF..ELSE..
/*! \brief Permet de savoir si le ligne est un "Si".

  Indique si la ligne est une ligne "Si".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Si", faux sinon.
*/
bool Dictionnaire::isSi(QString pLigne, QStringList* pListeArgs) {
    //récupération de toute les variable utilisateur
    QString  expression = listeQuantites();
    QRegExp rx("^si\\s(" + expression + ")(≤|≥|≠|=|>|>=|<|<=|!=)(" + expression + ")\\salors$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    if (rx.exactMatch(pLigne)) {
        if (pListeArgs)
            *pListeArgs = rx.capturedTexts();
        return true;
    } else
        return false;
}

/*! \brief Permet de savoir si le ligne est un "FinSi".

  Indique si la ligne est une ligne "FinSi".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "FinSi", faux sinon.
*/
bool Dictionnaire::isFinSi(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^finsi$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    return rx.exactMatch(pLigne);
}

/*! \brief Permet de savoir si le ligne est un "Sinon".

  Indique si la ligne est une ligne "Sinon".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Sinon", faux sinon.
*/
bool Dictionnaire::isSinon(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^sinon$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    return rx.exactMatch(pLigne);
}

//-----SWITCH
/*! \brief Permet de savoir si le ligne est un Selon.

  Indique si la ligne est une ligne "Selon".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Selon" , faux sinon.
*/
bool Dictionnaire::isSelon(QString pLigne, QStringList* pListeArgs) {
    QString expression = listeQuantites();
    QRegExp rx("^selon\\s?(" + expression + ")\\s?:?\\s?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    if (rx.exactMatch(pLigne)) {
        if (pListeArgs)
            *pListeArgs = rx.capturedTexts();
        return true;
    } else
        return false;
}

/*! \brief Permet de savoir si le ligne est un Cas(Differents choix du selon).

  Indique si la ligne est une ligne "Cas"(Differents choix du selon).

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Cas" , faux sinon.
*/
bool Dictionnaire::isCas(QString pLigne, QStringList* pListeArgs) {
    QString expression = listeQuantites();
    QRegExp rx("^cas\\s?(" + expression + ")\\s?:?\\s?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    if (rx.exactMatch(pLigne)) {
        if (pListeArgs)
            *pListeArgs = rx.capturedTexts();
        return true;
    } else
        return false;
}

/*! \brief Permet de savoir si le ligne est un Default (Cas par défault de Selon).

  Indique si la ligne est une ligne "Default" (Cas par défault de Selon).

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Default" (Cas par défault de Selon), faux sinon.
*/
bool Dictionnaire::isDefault(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^d[ée]faut\\s?:?\\s?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    return rx.exactMatch(pLigne);
}

/*! \brief Permet de savoir si le ligne est un FinSelon.

  Indique si la ligne est une ligne "FinSelon".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "FinSelon", faux sinon.
*/
bool Dictionnaire::isFinSelon(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^finselon\\s?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    return rx.exactMatch(pLigne);
}

//-----FOR
/*! \brief Permet de savoir si le ligne est un "Pour".

  Indique si la ligne est une ligne "Pour".
  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Pour", faux sinon.
*/
bool Dictionnaire::isPour(QString pLigne, QStringList* pListeArgs) {
    QString expression = listeQuantites();
    QRegExp rx("^pour\\s+(" + expression + ")\\s+de\\s+(" + expression + ")\\s+[àa]\\s+(" + expression + ")\\s+(\\[pas\\s+de\\s+(" + expression + ")\\]\\s+)?faire\\s?:?\\s?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    if (rx.exactMatch(pLigne)) {
        if (pListeArgs)
            *pListeArgs = rx.capturedTexts();
        return true;
    } else
        return false;
}

/*! \brief Permet de savoir si le ligne est un "FinPour".

  Indique si la ligne est une ligne "FinPour".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "FinPour", faux sinon.
*/
bool Dictionnaire::isFinPour(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^finpour$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    return rx.exactMatch(pLigne);
}

//-----DO..WHILE
/*! \brief Permet de savoir si le ligne est un "Repeter".

  Indique si la ligne est une ligne "Repeter".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Repeter", faux sinon.
*/
bool Dictionnaire::isRepeter(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^r[ée]p[ée]ter$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    return rx.exactMatch(pLigne);
}

/*! \brief Permet de savoir si le ligne est un "Jusqu'a".

  Indique si la ligne est une ligne "Jusqu'a".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "Jusqua", faux sinon.
*/
bool Dictionnaire::isJusqua(QString pLigne, QStringList* pListeArgs) {
    QString expression = listeQuantites();
    QRegExp rx("^jusqu[\\s']?[àa]\\s(" + expression + ")(≤|≥|≠|=|>|>=|<|<=|!=)(" + expression + ")\\s?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    if (rx.exactMatch(pLigne)) {
        if (pListeArgs)
            *pListeArgs = rx.capturedTexts();
        return true;
    } else
        return false;
}

//WHILE
/*! \brief Permet de savoir si le ligne est un "TantQue".

  Indique si la ligne est une ligne "TantQue".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "TantQue", faux sinon.
*/
bool Dictionnaire::isTantQue(QString pLigne, QStringList* pListeArgs) {
    QString expression = listeQuantites();
    QRegExp rx("^tantque\\s+(" + expression + ")(≤|≥|≠|=|>|>=|<|<=|!=)(" + expression + ")\\s?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    if (rx.exactMatch(pLigne)) {
        if (pListeArgs)
            *pListeArgs = rx.capturedTexts();
        return true;
    } else
        return false;
}

/*! \brief Permet de savoir si le ligne est un "FinTantQue".

  Indique si la ligne est une ligne "FinTantQue".

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un "FinTantQue", faux sinon.
*/
bool Dictionnaire::isFinTantQue(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^fintantque$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    return rx.exactMatch(pLigne);
}

/*! \brief Permet de savoir si le ligne est un affichage.

  Indique si la ligne est une ligne Afficher …

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est un affichage, faux sinon.
*/
bool Dictionnaire::isAfficher(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^afficher\\s+(.*)\\s?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    if (rx.exactMatch(pLigne)) {
        if (pListeArgs)
            *pListeArgs = rx.capturedTexts();
        return true;
    } else
        return false;
}

/*! \brief Permet de savoir si le ligne est une saisie.

  Indique si la ligne est une ligne Saisir variable.

  \todo Gestion des variables
  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est une saisie, faux sinon.
*/
bool Dictionnaire::isSaisir(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^saisir\\s+(" + listePipeVariable() + ")\\s?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    if (rx.exactMatch(pLigne)) {
        if (pListeArgs)
            *pListeArgs = rx.capturedTexts();
        return true;
    } else
        return false;
}

/*! \brief Permet de savoir si le ligne est une impression.

  Indique si la ligne est une ligne Imprimer …

  \param pLigne Ligne à analyser.
  \return Vrai si la ligne est une impression, faux sinon.
*/
bool Dictionnaire::isImprimer(QString pLigne, QStringList* pListeArgs) {
    QRegExp rx("^imprimer\\s+(" + listePipeVariable() + ")\\s?$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if (pListeArgs)
        pListeArgs->clear();
    if (rx.exactMatch(pLigne)) {
        if (pListeArgs)
            *pListeArgs = rx.capturedTexts();
        return true;
    } else
        return false;
}


//Expression réguliere de toute les variable séparé par un pipe
/*! \brief Permet de récupérer les variables du glossaire pour les transformer en chaîne de caractères, séparées d'un pipe.

  Transformation de la liste de variables du glossaire en : var1|var2|var3|...|varx

  \return String expression
*/
QString Dictionnaire::listePipeVariable() {
    QString expression = "(?:";
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

QString Dictionnaire::listeQuantites() {
    QString liste = listePipeVariable();
    QString expression = "(?:\\(*\\s*(?:[0-9]+(?:\\.[0-9]+)?\\s*\\)*)|";
    expression += liste;
    expression += "\\s*\\)*(?:[+\\-\\*/×÷]\\s*\\(*\\s*(?:(?:[0-9]+(?:\\.[0-9]+)?\\s*\\)*\\s*)|";
    expression += liste;
    expression += ")\\s*\\)*\\s*)*\\)*\\s*)";
    return expression;
}
