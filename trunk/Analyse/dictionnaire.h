#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H

#include <QtCore>

class Dictionnaire {
public:


    enum typeLigne {
        Si,        /*!< La variable recherch�e n'a pas �t� d�clar�e. */
        TantQue,       /*!< Lors de l'ajout d'une variable, une variable portant le m�me nom a d�j� �t� d�clar�e. */
        FinTantQue,              /*!< La variable a �t� d�clar�e avec un type diff�rent. */
        TypeInconnu,
    };

    static Dictionnaire::typeLigne getType(QString pLigne);
    static bool isSi(QString pLigne);

private:







};

#endif // DICTIONNAIRE_H
