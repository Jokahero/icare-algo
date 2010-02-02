#include "mathexp_tests.h"
#include "../arbre.h"
#include "../mathexp.h"

#include <QtTest/QSignalSpy>
#include <QtTest/QTest>

void MathExp_tests::testArbre() {
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

void MathExp_tests::testMathExp() {
    MathExp* m = new MathExp();
    QSignalSpy divisionParZeroSpy(m, SIGNAL(erreur(int)));
    m->setExpression("1/0");
    QCOMPARE(m->calcul(), (double)-1);
    m->setExpression("5*(4))");
    QCOMPARE(m->calcul(), (double)-1);
    QVERIFY(divisionParZeroSpy.isEmpty() == false);
    m->setExpression("3*5-2*2");
    QCOMPARE(m->calcul(), (double)11);
    m->setExpression("5+(3-2)*5");
    QCOMPARE(m->calcul(), (double)10);
    m->setExpression("5*(3-2)*5");
    QCOMPARE(m->calcul(), (double)25);
    m->setExpression("(1)");
    QCOMPARE(m->calcul(), (double)1);
    m->setExpression("2+(3+(1+1)*1)");
    QCOMPARE(m->calcul(), (double)7);
    m->setExpression("2+(3*(1+1)+1)");
    QCOMPARE(m->calcul(), (double)9);
    m->setExpression("2+(3*(1+1*(3-1))+1)");
    QCOMPARE(m->calcul(), (double)12);
    delete m;
}

QTEST_MAIN(MathExp_tests)
