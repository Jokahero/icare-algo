#ifndef MATHEXP_H
#define MATHEXP_H

#include "MathExp_global.h"
#include <QtCore>
#include "arbre.h"

class MATHEXPSHARED_EXPORT MathExp {
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
};

#endif // MATHEXP_H
