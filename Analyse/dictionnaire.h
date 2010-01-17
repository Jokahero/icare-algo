#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H

#include <QtCore>

class Dictionnaire {
public:


    enum typeLigne {
//Partie General
        Glossaire,
        DeclarationVariable,
        Debut,
        Fin,
        Commentaire,
        Affectation,
//if...else
        Si,
        FinSi,
        Sinon,
//switch
        Selon,
        Default,
        Cas,
        FinSelon,
//for
        Pour,
        FinPour,
//do..while
        Repeter,
        Jusqua,
//while
        TantQue,
        FinTantQue,




        TypeInconnu,
    };

    static typeLigne getType(QString pLigne);
//partie general
    static bool isGlossaire(QString pLigne);
    static bool isDeclarationVariable(QString pLigne);
    static bool isDebut(QString pLigne);
    static bool isFin(QString pLigne);
    static bool isCommentaire(QString pLigne);
//If
    static bool isSi(QString pLigne);
    static bool isFinSi(QString pLigne);
    static bool isSinon(QString pLigne);
//Switch
    static bool isSelon(QString pLigne);
    static bool isCas(QString pLigne);
    static bool isDefault(QString pLigne);
    static bool isFinSelon(QString pLigne);
//For
    static bool isPour(QString pLigne);
    static bool isFinPour(QString pLigne);

    static bool isRepeter(QString pLigne);

    static bool isTantQue(QString pLigne);
    static bool isFinTantQue(QString pLigne);

    static bool isJusqua(QString pLigne);

    static bool isAffectation(QString pLigne);




private:

    static QString listePipeVariable(/*QStringList*/);





};

#endif // DICTIONNAIRE_H
