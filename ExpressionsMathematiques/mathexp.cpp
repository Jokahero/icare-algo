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

    // Erreur de parenthèses
    if (pExpression.count("(") != pExpression.count(")")) {
        qDebug() << "Erreur de parentheses dans l'expression " << pExpression;
        emit erreur(Erreur::Parentheses);
        return NULL;
    }

    // Test de l'utilité des parenthèses : (1+1) → 1+1
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
            qDebug() << "Parentheses supprimees. Nouvelle expression : " << pExpression;
        }
    }

    if (pExpression.contains("(")) {
        qDebug() << "Parenthèses";
        int firstOP = pExpression.indexOf("(");

        if (firstOP > 0) {
            int i, cpt = 1;
            for (i = (firstOP + 1); i < pExpression.length() && cpt > 0; i++) {
                if (pExpression.at(i) == '(')
                    cpt++;
                else if (pExpression.at(i) == ')')
                    cpt--;
            }
            if (i < pExpression.length() && cpt == 0) {
                if ((pExpression.at(firstOP - 1) == '*' || pExpression.at(firstOP - 1) == '/') && (pExpression.at(i) == '+' || pExpression.at(i) == '-')) {
                    qDebug() << "contenu : " << pExpression.at(i);
                    t->setContenu(pExpression.at(i));
                    qDebug() << "sag : " << pExpression.left(i);
                    qDebug() << "sad : " << pExpression.right(pExpression.length() - i - 1);
                    t->setSag(parseExp(pExpression.left(i)));
                    t->setSad(parseExp(pExpression.right(pExpression.length() - i - 1)));
                } else {
                    qDebug() << "contenu : " << pExpression.at(firstOP - 1);
                    t->setContenu(pExpression.at(firstOP - 1));
                    qDebug() << "sag : " << pExpression.left(firstOP - 1);
                    qDebug() << "sad : " << pExpression.right(pExpression.length() - firstOP);
                    t->setSag(parseExp(pExpression.left(firstOP - 1)));
                    t->setSad(parseExp(pExpression.right(pExpression.length() - firstOP)));
                }
            } else {
                qDebug() << "contenu : " << pExpression.at(firstOP - 1);
                t->setContenu(pExpression.at(firstOP - 1));
                qDebug() << "sag : " << pExpression.left(firstOP - 1);
                qDebug() << "sad : " << pExpression.right(pExpression.length() - firstOP);
                t->setSag(parseExp(pExpression.left(firstOP - 1)));
                t->setSad(parseExp(pExpression.right(pExpression.length() - firstOP)));
            }

        } else if (pExpression.lastIndexOf(")") < pExpression.length()) {
            firstOP = pExpression.indexOf(")");
            qDebug() << "contenu : " << pExpression.at(firstOP + 1);
            qDebug() << "sag : " << pExpression.left(firstOP + 1);
            qDebug() << "sad : " << pExpression.right(pExpression.length() - firstOP - 2);

            t->setContenu(pExpression.at(firstOP + 1));
            t->setSag(parseExp(pExpression.left(firstOP + 1)));
            t->setSad(parseExp(pExpression.right(pExpression.length() - firstOP - 2)));
        }
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
        else {
            t->setContenu(pExpression);
        }
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
            qDebug() << "Division par 0 !";
            emit erreur(Erreur::DivisionParZero);
            return -1;
        }
    }
    else
        return -1;
}

Arbre* MathExp::getCalcul() {
    return m_calcul;
}
