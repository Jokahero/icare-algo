#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H

class QString;
class QStringList;

class Dictionnaire {
public:


    enum typeLigne {

        Glossaire,
        DeclarationVariable,
        Debut,
        Fin,
        Commentaire,
        Affectation,

        Si,
        FinSi,
        Sinon,

        Selon,
        Default,
        Cas,
        FinSelon,

        Pour,
        FinPour,

        Repeter,
        Jusqua,

        TantQue,
        FinTantQue,
        Afficher,
        Saisir,
        Imprimer,




        TypeInconnu,
    };

    static typeLigne getType(QString pLigne, QStringList* pListeArgs = 0);

    static bool isGlossaire(QString pLigne, QStringList* pListeArgs = 0);
    static bool isDeclarationVariable(QString pLigne, QStringList* pListeArgs = 0);
    static bool isDebut(QString pLigne, QStringList* pListeArgs = 0);
    static bool isFin(QString pLigne, QStringList* pListeArgs = 0);
    static bool isCommentaire(QString pLigne, QStringList* pListeArgs = 0);

    static bool isSi(QString pLigne, QStringList* pListeArgs = 0);
    static bool isFinSi(QString pLigne, QStringList* pListeArgs = 0);
    static bool isSinon(QString pLigne, QStringList* pListeArgs = 0);

    static bool isSelon(QString pLigne, QStringList* pListeArgs = 0);
    static bool isCas(QString pLigne, QStringList* pListeArgs = 0);
    static bool isDefault(QString pLigne, QStringList* pListeArgs = 0);
    static bool isFinSelon(QString pLigne, QStringList* pListeArgs = 0);

    static bool isPour(QString pLigne, QStringList* pListeArgs = 0);
    static bool isFinPour(QString pLigne, QStringList* pListeArgs = 0);

    static bool isRepeter(QString pLigne, QStringList* pListeArgs = 0);

    static bool isTantQue(QString pLigne, QStringList* pListeArgs = 0);
    static bool isFinTantQue(QString pLigne, QStringList* pListeArgs = 0);

    static bool isJusqua(QString pLigne, QStringList* pListeArgs = 0);

    static bool isAffectation(QString pLigne, QStringList* pListeArgs = 0);

    static bool isAfficher(QString pLigne, QStringList* pListeArgs = 0);
    static bool isSaisir(QString pLigne, QStringList* pListeArgs = 0);
    static bool isImprimer(QString pLigne, QStringList* pListeArgs = 0);




private:

    static QString listePipeVariable(/*QStringList*/);
    static QString listeQuantites(/*QStringList*/);
    static QString listeCondition();

};

#endif // DICTIONNAIRE_H
