#ifndef ERREURANALYSE_H
#define ERREURANALYSE_H

/*!
  \brief Constantes d'erreurs possibles lors de l'analyse d'un algorithme.
*/
class ErreurAnalyse {
public:
    enum {
        VariableNonDeclaree,        /*!< La variable recherchée n'a pas été déclarée. */
        VariableDejaDeclaree,       /*!< Lors de l'ajout d'une variable, une variable portant le même nom a déjà été déclarée. */
        TypeIncorrect,              /*!< La variable a été déclarée avec un type différent. */
    };
};

#endif // ERREURANALYSE_H
