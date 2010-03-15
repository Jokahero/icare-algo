#include "analyse_tests.h"

#include "../analyse.h"
#include "../arbre.h"
#include "../expressionlogique.h"
#include "../glossaire.h"
#include "../mathexp.h"

#include <QtCore/QDebug>
#include <QtTest/QTest>

void Analyse_tests::cleanupTestCase() {
    Analyse::getInstance()->destroy();
}

void Analyse_tests::testArbre() {
    Arbre* t1 = new Arbre();
    Arbre* t2 = new Arbre();
    Arbre* t3 = new Arbre("test", t1, t2);
    // Tests des sous arbres
    QVERIFY(t1->estFeuille());
    QVERIFY(!t3->estFeuille());
    QCOMPARE(t3->getSag(), t1);
    QCOMPARE(t3->getSad(), t2);
    t3->setSag(t2);
    t3->setSad(t1);
    QCOMPARE(t3->getSag(), t2);
    QCOMPARE(t3->getSad(), t1);
    // Tests du contenu
    QCOMPARE(t3->getContenu(), QString("test"));
    t3->setContenu("toto");
    QCOMPARE(t3->getContenu(), QString("toto"));
    // Tests de la hauteur
    QCOMPARE(t3->hauteur(), (unsigned int)1);
    QCOMPARE(t1->hauteur(), (unsigned int)0);
    t3->setSag(NULL);
    t3->setSad(NULL);
    QVERIFY(t3->estFeuille());
    QCOMPARE(t3->hauteur(), (unsigned int)0);
    delete t1;
    delete t2;
    delete t3;
}

void Analyse_tests::testGlossaire() {
    QVERIFY(!Analyse::getInstance()->getGlossaire()->existe("Toto"));
    QVERIFY(Analyse::getInstance()->getGlossaire()->ajoutEntier("Toto", "Variable de test"));
    QVERIFY(Analyse::getInstance()->getGlossaire()->existe("Toto"));
    QVERIFY(!Analyse::getInstance()->getGlossaire()->ajoutChaine("Toto", "test"));
    QVERIFY(Analyse::getInstance()->getGlossaire()->getValeurChaine("Toto") == QString::null);
    QVERIFY(Analyse::getInstance()->getGlossaire()->getValeurEntier("Toto") == 0);
    Analyse::getInstance()->getGlossaire()->setValeurEntier("Toto", 42);
    QVERIFY(Analyse::getInstance()->getGlossaire()->getValeurEntier("Toto") == 42);
}

void Analyse_tests::testMathExp() {
    MathExp* m = new MathExp();

    QFETCH(QString, exp);
    QFETCH(double, result);

    m->setExpression(exp);
    QCOMPARE(m->calcul(), result);

    delete m;
}

void Analyse_tests::testMathExp_data() {
    QTest::addColumn<QString>("exp");
    QTest::addColumn<double>("result");

    QTest::newRow("Division par 0") << "1/0" << (double)-1;
    QTest::newRow("Parenthèses incorrectes") << "5*(4))" << (double)-1;
    QTest::newRow("Priorités") << "3*5-2*2" << (double)11;
    QTest::newRow("Parenthèses/Priorités") << "5+(3-2)*5" << (double)10;
    QTest::newRow("Parenthèses/Priorités") << "5*(3-2)*5" << (double)25;
    QTest::newRow("Parenthèses inutiles") << "(1)" << (double)1;
    QTest::newRow("Parenthèses inutiles") << "((5+(3-2)*5))" << (double)10;
    QTest::newRow("Parenthèses/Priorités") << "2+(3+(1+1)*1)" << (double)7;
    QTest::newRow("Parenthèses/Priorités") << "2+(3*(1+1)+1)" << (double)9;
    QTest::newRow("Parenthèses/Priorités") << "2+(3*(1+1*(3-1))+1)" << (double)12;
    QTest::newRow("Nombres négatifs") << "-5 + 1" << (double)-4;
    for (int i = -5; i < 50; i++)
        QTest::newRow("") << QString::number(i*i) + " - (" + QString::number(i) + ") * (" + QString::number(i) + ")" << (double)0;
}

void Analyse_tests::testExpressionLogique() {
    ExpressionLogique* e = new ExpressionLogique();

    QFETCH(QString, exp);
    QFETCH(bool, result);
    e->setExpression(exp);
    QCOMPARE(e->resultat(), result);
    delete e;
}

void Analyse_tests::testExpressionLogique_data() {
    QTest::addColumn<QString>("exp");
    QTest::addColumn<bool>("result");

    QTest::newRow("=") << "1 = 2" << false;
    QTest::newRow("=") << "1 = 1" << true;
    QTest::newRow("!=") << "1 != 1" << false;
    QTest::newRow("!=") << "1 != 2" << true;
    QTest::newRow("≠") << "1 " + QString(QChar(0x2260)) + " 1" << false;
    QTest::newRow("≠") << "1 " + QString(QChar(0x2260)) + " 2" << true;
    QTest::newRow(">") << "1 > 2" << false;
    QTest::newRow(">") << "2 > 1" << true;
    QTest::newRow("<") << "2 < 1" << false;
    QTest::newRow("<") << "1 < 2" << true;
    QTest::newRow(">=") << "1 >= 2" << false;
    QTest::newRow(">=") << "2 >= 1" << true;
    QTest::newRow(">=") << "1 >= 2" << false;
    QTest::newRow(">=") << "2 >= 2" << true;
    QTest::newRow("≥") << "1 " + QString(QChar(0x2265)) + " 2" << false;
    QTest::newRow("≥") << "2 " + QString(QChar(0x2265)) + " 1" << true;
    QTest::newRow("≥") << "1 " + QString(QChar(0x2265)) + " 2" << false;
    QTest::newRow("≥") << "2 " + QString(QChar(0x2265)) + " 2" << true;
    QTest::newRow("<=") << "2 <= 1" << false;
    QTest::newRow("<=") << "1 <= 2" << true;
    QTest::newRow("<=") << "2 <= 1" << false;
    QTest::newRow("<=") << "2 <= 2" << true;
    QTest::newRow("≤") << "2 " + QString(QChar(0x2264)) + " 1" << false;
    QTest::newRow("≤") << "1 " + QString(QChar(0x2264)) + " 2" << true;
    QTest::newRow("≤") << "2 " + QString(QChar(0x2264)) + " 1" << false;
    QTest::newRow("≤") << "2 " + QString(QChar(0x2264)) + " 2" << true;
    QTest::newRow("Parenthèses") << "(2 = 2) || (3 " + QString(QChar(0x2260)) + " 3)" << true;
    QTest::newRow("Parenthèses") << "(2 = 2) && (3 " + QString(QChar(0x2260)) + " 3)" << false;
    QTest::newRow("Priorités") << "2 = 2 || 3 " + QString(QChar(0x2260)) + " 3" << true;
    QTest::newRow("Priorités") << "2 = 2 && 3 " + QString(QChar(0x2260)) + " 3" << false;
    QTest::newRow("Parenthèses/Priorités") << "(3 < 4 || 5 > 9) && 1 = 1 || 5 > 6" << true;
    QTest::newRow("Expressions mathématiques") << "3 + 1 != 4" << false;
    QTest::newRow("Expressions mathématiques") << "3 + 1 = 4" << true;
}
