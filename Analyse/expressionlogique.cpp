#include "expressionlogique.h"

#include <QtCore/QString>


ExpressionLogique::ExpressionLogique(int pNumLigne) : m_numLigne(pNumLigne) {
    m_calcul = new Arbre();
    m_expression = QString::null;
}

ExpressionLogique::~ExpressionLogique() {
    delete m_calcul;
}

void ExpressionLogique::setExpression(const QString& pExpression) {
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

Arbre* ExpressionLogique::parseExp(const QString& pExpression) {
    QString expression = pExpression.simplified();
    if (expression == QString::null)
        return NULL;
    Arbre* t = new Arbre();

    // Erreur de parenthèses
    if (expression.count("(") != expression.count(")")) {
        emit sigErreur(ExpressionLogique::Parentheses, m_numLigne);
        return parseExp("-1");
    }

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
            return parseExp(pExpression);
        }
    }

    int taille;
    int rang = moinsPrioritaire(expression, &taille);
    if (rang == -1)
        t->setContenu(expression);
    else {
        QString contenu = QString::null;
        for (int i = 0; i < taille; i++)
            contenu.append(expression.at(rang + i));
        t->setContenu(contenu);
        t->setSag(parseExp(expression.left(rang)));
        t->setSad(parseExp(expression.right(expression.length() - rang - taille)));
    }

    return t;
}

bool ExpressionLogique::calculRec(Arbre* pArbre) {
    if (pArbre->estFeuille())
        return false;

    if (pArbre->getSag()->estFeuille()) {
        MathExp* me = new MathExp(m_numLigne);
        connect(me, SIGNAL(sigErreur(MathExp::erreur, int)), this, SIGNAL(sigErreurMath(MathExp::erreur, int)));
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
        else if (pArbre->getContenu() == QString(QChar(0x2264)) || pArbre->getContenu() == "<=")
            return (g <= d);
        else if (pArbre->getContenu() == QString(QChar(0x2265)) || pArbre->getContenu() == ">=")
            return (g >= d);
        else if (pArbre->getContenu() == QString(QChar(0x2260)) || pArbre->getContenu() == "!=")
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
        else if (pArbre->getContenu() == QString(QChar(0x2260)) || pArbre->getContenu() == "!=")
            return calculRec(pArbre->getSag()) != calculRec(pArbre->getSad());
        else
            return false;
    }
}

Arbre* ExpressionLogique::getArbre() {
    return m_calcul;
}

int ExpressionLogique::moinsPrioritaire(const QString& pExpression, int* pTaille) {
    QString expression = pExpression;
    *pTaille = 1;
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

    if (expression.contains("||")) {
        *pTaille = 2;
        return expression.indexOf("||");
    } else if (expression.contains("&&")) {
        *pTaille = 2;
        return expression.indexOf("&&");
    } else if (expression.contains("!=")) {
        *pTaille = 2;
        return expression.indexOf("!=");
    } else if (expression.contains("<=")) {
        *pTaille = 2;
        return expression.indexOf("<=");
    } else if (expression.contains(">=")) {
        *pTaille = 2;
        return expression.indexOf(">=");
    } else if (expression.contains('<'))
        return expression.indexOf('<');
    else if (expression.contains('>'))
        return expression.indexOf('>');
    else if (expression.contains('='))
        return expression.indexOf('=');
    else if (expression.contains(QString(QChar(0x2264)))) {    // ≤
        *pTaille = QString(QChar(0x2264)).length();
        return expression.indexOf(QString(QChar(0x2264)));
    } else if (expression.contains(QString(QChar(0x2265)))) {  // ≥
        *pTaille = QString(QString(QChar(0x2265))).length();
        return expression.indexOf(QString(QChar(0x2265)));
    } else if (expression.contains(QString(QChar(0x2260)))) {  // ≠
        *pTaille = QString(QChar(0x2260)).length();
        return expression.indexOf(QString(QChar(0x2260)));
    } else
        return -1;
}
