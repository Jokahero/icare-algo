#ifndef MATHEXP_H
#define MATHEXP_H

#include "MathExp_global.h"
#include "arbre.h"

#include <QtCore/QObject>

/*! \brief Résout une expression mathématique.

  Les priorités des opérations (+-×÷) sont respectées, ainsi que les parenthèses.
*/
class MathExp : public QObject {

    Q_OBJECT

public:
    MathExp();
    void setExpression(QString pExpression);
    double calcul();
    Arbre* getCalcul();

    enum erreur {
        DivisionParZero,        /*!< Une division par zéro a été rencontrée dans l'expression. */
        PositionOperateurs,     /*!< Deux opérateurs ou plus se succèdent (3+×3). */
        Parentheses,            /*!< Le nombre de parenthèses ouvrantes de l'expression est différent du nombre de parenthèses fermantes. */
    };

private:
    Arbre* parseExp(QString pExpression);
    double calculRec(Arbre* pArbre);

    QString m_expression;                       /*!<\brief Expression mathématique à calculer. */
    Arbre* m_calcul;                            /*!<\brief Racine de l'arbre utilisé pour le calcul. */

signals:
    void sigErreur(MathExp::erreur);
};

#endif // MATHEXP_H
