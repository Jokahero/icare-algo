#include "analyse_tests.h"

#include "../analyse.h"
#include "../arbre.h"
#include "../glossaire.h"
#include "../mathexp.h"

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
}

QTEST_MAIN(Analyse_tests)
