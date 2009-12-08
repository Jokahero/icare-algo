#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H

#include <QtCore>

class Dictionnaire {
public:


    enum typeLigne {
        Si,        /*!< La variable recherchée n'a pas été déclarée. */
        TantQue,       /*!< Lors de l'ajout d'une variable, une variable portant le même nom a déjà été déclarée. */
        FinTantQue,              /*!< La variable a été déclarée avec un type différent. */
        TypeInconnu,
    };

    static Dictionnaire::typeLigne getType(QString pLigne);
    static bool isSi(QString pLigne);

private:







};

#endif // DICTIONNAIRE_H
