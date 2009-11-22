#ifndef ERREUR_H
#define ERREUR_H

/*!
  \brief Constantes d'erreurs possibles lors de l'analyse d'expressions mathématiques.
*/
class Erreur {
public:
    enum {
        DivisionParZero,        /*!< Une division par zéro a été rencontrée dans l'expression. */
        PositionOperateurs,     /*!< Deux opérateurs ou plus se succèdent (3+×3). */
        Parentheses,            /*!< Le nombre de parenthèses ouvrantes de l'expression est différent du nombre de parenthèses fermantes. */
    };
};

#endif // ERREUR_H
