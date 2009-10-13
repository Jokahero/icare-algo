#include "mathexp.h"


MathExp::MathExp() {
    m_calcul = new Arbre();
    m_expression = QString::null;
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
    qDebug() << "Parsing " << pExpression;
    if (pExpression == QString::null)
        return NULL;
    Arbre* t = new Arbre();

    if (pExpression.startsWith("(") && pExpression.endsWith(")")) {
        QString str = pExpression.left(pExpression.length() - 1);
        str = str.right(str.length() - 1);
        return parseExp(str);
    } else if (pExpression.startsWith("(") && !pExpression.endsWith(")")) {
        int lp = pExpression.lastIndexOf(")") + 1;
        qDebug() << "PARENTHESES";
        qDebug() << "Contenu : " << pExpression.at(lp);
        qDebug() << "Sag : " << pExpression.left(lp);
        qDebug() << "Sad : " << pExpression.right(pExpression.length() - lp - 1);
        t->setContenu(pExpression.at(lp));
        t->setSag(parseExp(pExpression.left(lp)));
        t->setSad(parseExp(pExpression.right(pExpression.length() - lp - 1)));
    } else {
        if (pExpression.contains("+")) {
            t->setContenu("+");
            t->setSag(parseExp(pExpression.left(pExpression.indexOf("+"))));
            t->setSad(parseExp(pExpression.right(pExpression.length() - pExpression.indexOf("+") - 1)));
        }
        else if (pExpression.contains("-")) {
            t->setContenu("-");
            t->setSag(parseExp(pExpression.left(pExpression.indexOf("-"))));
            t->setSad(parseExp(pExpression.right(pExpression.length() - pExpression.indexOf("-") - 1)));
        }
        else if (pExpression.contains("*")) {
            t->setContenu("*");
            t->setSag(parseExp(pExpression.left(pExpression.indexOf("*"))));
            t->setSad(parseExp(pExpression.right(pExpression.length() - pExpression.indexOf("*") - 1)));
        }
        else if (pExpression.contains("/")) {
            t->setContenu("/");
            t->setSag(parseExp(pExpression.left(pExpression.indexOf("/"))));
            t->setSad(parseExp(pExpression.right(pExpression.length() - pExpression.indexOf("/") - 1)));
        }
        else
            t->setContenu(pExpression);
    }



    return t;
}

double MathExp::calculRec(Arbre* pArbre) {
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
            qDebug() << "Division par 0 !";
            return -1;
        }
    }
    else
        return -1;
}

Arbre* MathExp::getCalcul() {
    return m_calcul;
}
