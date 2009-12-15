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

    static typeLigne getType(QString pLigne);

    static bool isGlossaire(QString pLigne);
    static bool isDeclarationVariable(QString pLigne);
    static bool isDebut(QString pLigne);
    static bool isFin(QString pLigne);
    static bool isCommentaire(QString pLigne);

    static bool isFinPour(QString pLigne);

    static bool isDefault(QString pLigne);
    static bool isFinSelon(QString pLigne);

    static bool isRepeter(QString pLigne);

    static bool isSi(QString pLigne);
    static bool isFinSi(QString pLigne);
    static bool isSinon(QString pLigne);






private:

    QString listePipeVariable(QStringList);





};

#endif // DICTIONNAIRE_H
