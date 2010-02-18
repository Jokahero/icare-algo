#include "mathexp.h"

#include <QtCore/QString>


MathExp::MathExp() {
    m_calcul = new Arbre();
    m_expression = QString::null;
}

MathExp::~MathExp() {
    delete m_calcul;
}

void MathExp::setExpression(QString pExpression) {
    m_expression = pExpression;
}

double MathExp::calcul() {
    if (m_expression == QString::null)
        return 0;
    m_calcul = parseExp(m_expression);
    return calculRec(m_calcul);
}

Arbre* MathExp::parseExp(QString pExpression) {
    pExpression = pExpression.simplified();
    if (pExpression == QString::null)
        return NULL;
    Arbre* t = new Arbre();

    // Erreur de parenthèses
    if (pExpression.count("(") != pExpression.count(")")) {
        emit sigErreur(MathExp::Parentheses);
        return parseExp("-1");
    }

    // Test de l'utilité des parenthèses : (1+1) → 1+1
    if (pExpression.left(1) == "(" && pExpression.right(1) == ")") {
        int i, cpt = 1;
        for (i = 1; i < pExpression.length() && cpt > 0; i++) {
            if (pExpression.at(i) == '(')
                cpt++;
            else if (pExpression.at(i) == ')')
                cpt--;
        }

        if (i == pExpression.length() && cpt == 0) {
            pExpression = pExpression.left(pExpression.length() - 1);
            pExpression = pExpression.right(pExpression.length() - 1);
            return parseExp(pExpression);
        }
    }

    int rang = moinsPrioritaire(pExpression);
    if (rang == -1)
        t->setContenu(pExpression);
    else {
        t->setContenu(pExpression.at(rang));
        t->setSag(parseExp(pExpression.left(rang)));
        t->setSad(parseExp(pExpression.right(pExpression.length() - rang - 1)));
    }

    return t;
}

double MathExp::calculRec(Arbre* pArbre) {
    if (pArbre->estFeuille())
        return pArbre->getContenu().toDouble();
    double g, d;
    if (pArbre->getSag()->estFeuille())
        g = pArbre->getSag()->getContenu().toDouble();
    else
        g = calculRec(pArbre->getSag());
    if (pArbre->getSad()->estFeuille())
        d = pArbre->getSad()->getContenu().toDouble();
    else
        d = calculRec(pArbre->getSad());

    if (pArbre->getContenu() == QString("+"))
        return (g + d);
    else if (pArbre->getContenu() == QString("-"))
        return (g - d);
    else if (pArbre->getContenu() == QString("*"))
        return (g * d);
    else if (pArbre->getContenu() == QString("/")) {
        if (d != 0)
            return (g / d);
        else {
            emit sigErreur(MathExp::DivisionParZero);
            return -1;
        }
    }
    else
        return -1;
}

Arbre* MathExp::getCalcul() {
    return m_calcul;
}

int MathExp::moinsPrioritaire(QString pExpression) {
    while (pExpression.contains('(')) {
        int firstOP = pExpression.indexOf("(");
        int i, cpt = 1;
        for (i = (firstOP + 1); i < pExpression.length() && cpt > 0; i++) {
            if (pExpression.at(i) == '(')
                cpt++;
            else if (pExpression.at(i) == ')')
                cpt--;
        }

        for (int j = firstOP; j < i; j++)
            pExpression[j] = ' ';
    }

    if (pExpression.contains('+'))
        return pExpression.indexOf('+');
    else if (pExpression.contains('-'))
        return pExpression.indexOf('-');
    else if (pExpression.contains('*'))
        return pExpression.indexOf('*');
    else if (pExpression.contains('/'))
        return pExpression.indexOf('/');
    else
        return -1;
}
