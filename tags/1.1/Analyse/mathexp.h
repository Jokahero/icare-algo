#ifndef MATHEXP_H
#define MATHEXP_H

#include "arbre.h"

#include <QtCore/QObject>

/*! \brief Résout une expression mathématique.

  Les priorités des opérations (+-×÷) sont respectées, ainsi que les parenthèses.
*/
class MathExp : public QObject {
    Q_OBJECT

public:
    MathExp(int pNumLigne = -1);
    ~MathExp();
    void setExpression(const QString& pExpression);
    double calcul();
    Arbre* getCalcul() const;

    enum erreur {
        DivisionParZero,        /*!< Une division par zéro a été rencontrée dans l'expression. */
        PositionOperateurs,     /*!< Deux opérateurs ou plus se succèdent (3+×3). */
        Parentheses,            /*!< Le nombre de parenthèses ouvrantes de l'expression est différent du nombre de parenthèses fermantes. */
    };

private:
    Arbre* parseExp(const QString& pExpression);
    double calculRec(Arbre* pArbre) const;
    int m_numLigne;

    int moinsPrioritaire(const QString& pExpression) const;

    QString m_expression;                       /*!< \brief Expression mathématique à calculer. */
    Arbre* m_calcul;                            /*!< \brief Racine de l'arbre utilisé pour le calcul. */

signals:
    void sigErreur(MathExp::erreur pErreur, int pNumLigne) const;
};

#endif // MATHEXP_H
