#ifndef EXPRESSIONLOGIQUE_H
#define EXPRESSIONLOGIQUE_H

#include "arbre.h"
#include "mathexp.h"

#include <QtCore/QObject>

/*! \brief Calcule le résultat d'une expression logique

  Les priorités des opérations (et/ou) sont respectées, ainsi que les parenthèses.
*/
class ExpressionLogique : public QObject {
    Q_OBJECT

public:
    ExpressionLogique(int pNumLigne = -1);
    ~ExpressionLogique();
    void setExpression(QString pExpression);
    QString getExpression() const;
    bool resultat();
    Arbre* getArbre();

    enum erreur {
        PositionOperateurs,     /*!< Deux opérateurs ou plus se succèdent (3+×3). */
        Parentheses,            /*!< Le nombre de parenthèses ouvrantes de l'expression est différent du nombre de parenthèses fermantes. */
    };

private:
    Arbre* parseExp(QString pExpression);
    bool calculRec(Arbre* pArbre);
    int m_numLigne;

    int moinsPrioritaire(QString pExpression, int* pTaille);

    QString m_expression;                       /*!< \brief Expression logique à vérifier. */
    Arbre* m_calcul;                            /*!< \brief Racine de l'arbre utilisé pour la vérification. */

signals:
    void sigErreur(ExpressionLogique::erreur pErreur, int pNumLigne);
    void sigErreurMath(MathExp::erreur pErreur, int pNumLigne);
};

#endif // EXPRESSIONLOGIQUE_H
