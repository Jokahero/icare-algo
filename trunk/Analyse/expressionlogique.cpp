#include "expressionlogique.h"

#include "mathexp.h"

#include <QtCore/QString>


ExpressionLogique::ExpressionLogique() {
    m_calcul = new Arbre();
    m_expression = QString::null;
}

ExpressionLogique::~ExpressionLogique() {
    delete m_calcul;
}

void ExpressionLogique::setExpression(QString pExpression) {
    m_expression = pExpression;
}

QString ExpressionLogique::getExpression() const {
    return m_expression;
}

bool ExpressionLogique::resultat() {
    if (m_expression == QString::null)
        return false;
    m_calcul = parseExp(m_expression);
    return calculRec(m_calcul);
}

Arbre* ExpressionLogique::parseExp(QString pExpression) {
    if (pExpression == QString::null)
        return NULL;
    Arbre* t = new Arbre();
    pExpression = pExpression.trimmed();

    // Erreur de parenthèses
    if (pExpression.count("(") != pExpression.count(")")) {
        emit sigErreur(ExpressionLogique::Parentheses);
        return parseExp("-1");
    }

    // Test de l'utilité des parenthèses : (1>1) → 1>1
    if (pExpression.left(1) == "(" && pExpression.right(1) == ")") {
        int i, cpt = 0;
        for (i = 1; i < pExpression.length() && cpt > 0; i++) {
            if (pExpression.at(i) == '(')
                cpt++;
            else if (pExpression.at(i) == ')')
                cpt--;
        }

        if (i < pExpression.length() && cpt == 0) {
            pExpression = pExpression.left(pExpression.length() - 1);
            pExpression = pExpression.right(pExpression.length() - 1);
            return parseExp(pExpression);
        }
    }

    int taille;
    int rang = moinsPrioritaire(pExpression, &taille);
    if (rang == -1)
        t->setContenu(pExpression);
    else {
        QString contenu = QString::null;
        for (int i = 0; i < taille; i++)
            contenu.append(pExpression.at(rang + i));
        t->setContenu(contenu);
        t->setSag(parseExp(pExpression.left(rang)));
        t->setSad(parseExp(pExpression.right(pExpression.length() - rang - taille)));
    }

    return t;
}

bool ExpressionLogique::calculRec(Arbre* pArbre) {
    if (pArbre->estFeuille())
        return false;

    if (pArbre->getSag()->estFeuille()) {
        MathExp* me = new MathExp();
        me->setExpression(pArbre->getSag()->getContenu());
        double g = me->calcul();
        me->setExpression(pArbre->getSad()->getContenu());
        double d = me->calcul();
        delete me;
        if (pArbre->getContenu() == "<")
            return (g < d);
        else if (pArbre->getContenu() == ">")
            return (g > d);
        else if (pArbre->getContenu() == "=")
            return (g == d);
        else if (pArbre->getContenu() == "≤" || pArbre->getContenu() == "<=")
            return (g <= d);
        else if (pArbre->getContenu() == "≥" || pArbre->getContenu() == ">=")
            return (g >= d);
        else if (pArbre->getContenu() == "≠" || pArbre->getContenu() == "!=")
            return (g != d);
        else
            return false;
    } else {
        if (pArbre->getContenu() == "||")
            return calculRec(pArbre->getSag()) || calculRec(pArbre->getSad());
        else if (pArbre->getContenu() == "&&")
            return calculRec(pArbre->getSag()) && calculRec(pArbre->getSad());
        else if (pArbre->getContenu() == "=")
            return calculRec(pArbre->getSag()) == calculRec(pArbre->getSad());
        else if (pArbre->getContenu() == "≠" || pArbre->getContenu() == "!=")
            return calculRec(pArbre->getSag()) != calculRec(pArbre->getSad());
        else
            return false;
    }
}

Arbre* ExpressionLogique::getArbre() {
    return m_calcul;
}

int ExpressionLogique::moinsPrioritaire(QString pExpression, int* pTaille) {
    *pTaille = 1;
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

    if (pExpression.contains("||")) {
        *pTaille = 2;
        return pExpression.indexOf("||");
    } else if (pExpression.contains("&&")) {
        *pTaille = 2;
        return pExpression.indexOf("&&");
    } else if (pExpression.contains("!=")) {
        *pTaille = 2;
        return pExpression.indexOf("!=");
    } else if (pExpression.contains("<=")) {
        *pTaille = 2;
        return pExpression.indexOf("<=");
    } else if (pExpression.contains(">=")) {
        *pTaille = 2;
        return pExpression.indexOf(">=");
    } else if (pExpression.contains('<'))
        return pExpression.indexOf('<');
    else if (pExpression.contains('>'))
        return pExpression.indexOf('>');
    else if (pExpression.contains('='))
        return pExpression.indexOf('=');
    else if (pExpression.contains("≤")) {
        *pTaille = QString("≤").length();
        return pExpression.indexOf("≤");
    } else if (pExpression.contains("≥")) {
        *pTaille = QString("≥").length();
        return pExpression.indexOf("≥");
    } else if (pExpression.contains("≠")) {
        *pTaille = QString("≠").length();
        return pExpression.indexOf("≠");
    } else
        return -1;
}
