#ifndef MATHEXP_TESTS_H
#define MATHEXP_TESTS_H

#include <QObject>
#include <QtCore>
#include <QtTest>

/*! \brief Tests du module d'expressions mathématiques.

  Teste \em Arbre et MathExp.
*/
class MathExp_tests : public QObject {
    Q_OBJECT
private slots:
    void testArbre();
    void testMathExp();
};

#endif // MATHEXP_TESTS_H
