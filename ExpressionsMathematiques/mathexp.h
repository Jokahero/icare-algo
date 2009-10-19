#ifndef MATHEXP_H
#define MATHEXP_H

#include "MathExp_global.h"
#include <QtCore>
#include "arbre.h"

/*! \brief Résout une expression mathématique.

  Les priorités des opérations (+-×÷) sont respectées, ainsi que les parenthèses.
*/
class MATHEXPSHARED_EXPORT MathExp : public QObject {

    Q_OBJECT

public:
    MathExp();
    void setExpression(QString pExpression);
    double calcul();
    Arbre* getCalcul();

private:
    Arbre* parseExp(QString pExpression);
    double calculRec(Arbre* pArbre);

    QString m_expression;
    Arbre* m_calcul;

signals:
    void divisionParZero();
};

#endif // MATHEXP_H
