#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H

class QString;
class QStringList;

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
        Afficher,
        Saisir,
        Imprimer,




        TypeInconnu,
    };

    static typeLigne getType(QString pLigne, QStringList* pListeArgs = 0);
    //partie general
    static bool isGlossaire(QString pLigne, QStringList* pListeArgs = 0);
    static bool isDeclarationVariable(QString pLigne, QStringList* pListeArgs = 0);
    static bool isDebut(QString pLigne, QStringList* pListeArgs = 0);
    static bool isFin(QString pLigne, QStringList* pListeArgs = 0);
    static bool isCommentaire(QString pLigne, QStringList* pListeArgs = 0);
    //If
    static bool isSi(QString pLigne, QStringList* pListeArgs = 0);
    static bool isFinSi(QString pLigne, QStringList* pListeArgs = 0);
    static bool isSinon(QString pLigne, QStringList* pListeArgs = 0);
    //Switch
    static bool isSelon(QString pLigne, QStringList* pListeArgs = 0);
    static bool isCas(QString pLigne, QStringList* pListeArgs = 0);
    static bool isDefault(QString pLigne, QStringList* pListeArgs = 0);
    static bool isFinSelon(QString pLigne, QStringList* pListeArgs = 0);
    //For
    static bool isPour(QString pLigne, QStringList* pListeArgs = 0);
    static bool isFinPour(QString pLigne, QStringList* pListeArgs = 0);

    static bool isRepeter(QString pLigne, QStringList* pListeArgs = 0);

    static bool isTantQue(QString pLigne, QStringList* pListeArgs = 0);
    static bool isFinTantQue(QString pLigne, QStringList* pListeArgs = 0);

    static bool isJusqua(QString pLigne, QStringList* pListeArgs = 0);

    static bool isAffectation(QString pLigne, QStringList* pListeArgs = 0);
    // Fonctions
    static bool isAfficher(QString pLigne, QStringList* pListeArgs = 0);
    static bool isSaisir(QString pLigne, QStringList* pListeArgs = 0);
    static bool isImprimer(QString pLigne, QStringList* pListeArgs = 0);




private:

    static QString listePipeVariable(/*QStringList*/);
    static QString listeQuantites(/*QStringList*/);

};

#endif // DICTIONNAIRE_H
