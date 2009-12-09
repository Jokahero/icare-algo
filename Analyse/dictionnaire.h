#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H

#include <QtCore>

class Dictionnaire {
public:


    enum typeLigne {
        Glossaire,
        DeclarationVariable,
        Debut,
        Fin,
        Commentaire,

        FinPour,

        Default,
        FinSelon,

        Repeter,
        Si,
        FinSi,
        Sinon,

        TypeInconnu,
    };

    static Dictionnaire::typeLigne getType(QString pLigne);

    static bool Dictionnaire::isGlossaire(QString pLigne);
    static bool Dictionnaire::isDeclarationVariable(QString pLigne);
    static bool Dictionnaire::isDebut(QString pLigne);
    static bool Dictionnaire::isFin(QString pLigne);
    static bool Dictionnaire::isCommentaire(QString pLigne);

    static bool Dictionnaire::isFinPour(QString pLigne);

    static bool Dictionnaire::isDefault(QString pLigne);
    static bool Dictionnaire::isFinSelon(QString pLigne);

    static bool Dictionnaire::isRepeter(QString pLigne);

    static bool Dictionnaire::isSi(QString pLigne);
    static bool Dictionnaire::isFinSi(QString pLigne);
    static bool Dictionnaire::isSinon(QString pLigne);






private:







};

#endif // DICTIONNAIRE_H
