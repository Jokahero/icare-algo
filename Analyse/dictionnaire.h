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
//if...else
        Si,
        FinSi,
        Sinon,
//switch
        Selon,
        Default,
        Cas,
        FinSelon,


        FinPour,


        Repeter,



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
    static bool isFinPour(QString pLigne);

    static bool isRepeter(QString pLigne);





private:

    QString listePipeVariable(QStringList);





};

#endif // DICTIONNAIRE_H
