#ifndef MATHEXP_TESTS_H
#define MATHEXP_TESTS_H

#include <QObject>
#include <QtCore>
#include <QtTest>

class MathExp_tests : public QObject {
    Q_OBJECT
private slots:
    void testArbre();
    void testMathExp();
};

#endif // MATHEXP_TESTS_H
