#include "mathexp.h"

#include <QtCore/QString>


MathExp::MathExp(int pNumLigne) : m_numLigne(pNumLigne) {
    m_calcul = new Arbre();
    m_expression = QString::null;
}

MathExp::~MathExp() {
    delete m_calcul;
}

void MathExp::setExpression(const QString& pExpression) {
    m_expression = pExpression;
}

double MathExp::calcul() {
    if (m_expression == QString::null)
        return 0;
    m_calcul = parseExp(m_expression);
    return calculRec(m_calcul);
}

Arbre* MathExp::parseExp(const QString& pExpression) {
    QString expression = pExpression.simplified();
    if (expression == QString::null)
        return NULL;
    Arbre* t = new Arbre();

    // Erreur de parenthèses
    if (expression.count("(") != expression.count(")")) {
        emit sigErreur(MathExp::Parentheses, m_numLigne);
        return parseExp("-1");
    }

    // Test de l'utilité des parenthèses : (1+1) → 1+1
    if (expression.left(1) == "(" && expression.right(1) == ")") {
        int i, cpt = 1;
        for (i = 1; i < expression.length() && cpt > 0; i++) {
            if (expression.at(i) == '(')
                cpt++;
            else if (expression.at(i) == ')')
                cpt--;
        }

        if (i == expression.length() && cpt == 0) {
            expression = expression.left(expression.length() - 1);
            expression = expression.right(expression.length() - 1);
            return parseExp(expression);
        }
    }

    int rang = moinsPrioritaire(expression);
    if (rang == -1)
        t->setContenu(expression);
    else {
        t->setContenu(expression.at(rang));
        t->setSag(parseExp(expression.left(rang)));
        t->setSad(parseExp(expression.right(expression.length() - rang - 1)));
    }

    return t;
}

double MathExp::calculRec(Arbre* pArbre) const {
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
    else if (pArbre->getContenu() == QString("%"))
        return ((int)g % (int)d);
    else if (pArbre->getContenu() == QString("/")) {
        if (d != 0)
            return (g / d);
        else {
            emit sigErreur(MathExp::DivisionParZero, m_numLigne);
            return -1;
        }
    }
    else
        return -1;
}

Arbre* MathExp::getCalcul() const {
    return m_calcul;
}

int MathExp::moinsPrioritaire(const QString& pExpression) const {
    QString expression = pExpression;
    while (expression.contains('(')) {
        int firstOP = expression.indexOf("(");
        int i, cpt = 1;
        for (i = (firstOP + 1); i < expression.length() && cpt > 0; i++) {
            if (expression.at(i) == '(')
                cpt++;
            else if (expression.at(i) == ')')
                cpt--;
        }

        for (int j = firstOP; j < i; j++)
            expression[j] = ' ';
    }

    if (expression.contains('+'))
        return expression.indexOf('+');
    else if (expression.contains('-'))
        return expression.indexOf('-');
    else if (expression.contains('*'))
        return expression.indexOf('*');
    else if (expression.contains('%'))
        return expression.indexOf('%');
    else if (expression.contains('/'))
        return expression.indexOf('/');
    else
        return -1;
}
