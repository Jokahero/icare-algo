#include "mathexp_tests.h"
#include "../arbre.h"
#include "../mathexp.h"

void MathExp_tests::testArbre() {
    Arbre* t1 = new Arbre();
    Arbre* t2 = new Arbre();
    Arbre* t3 = new Arbre("test", t1, t2);
    QVERIFY(t1->estFeuille());
    QVERIFY(!t3->estFeuille());
    QCOMPARE(t3->getSag(), t1);
    QCOMPARE(t3->getSad(), t2);
    t3->setSag(t2);
    t3->setSad(t1);
    QCOMPARE(t3->getSag(), t2);
    QCOMPARE(t3->getSad(), t1);
    QCOMPARE(t3->getContenu(), QString("test"));
    t3->setContenu("toto");
    QCOMPARE(t3->getContenu(), QString("toto"));
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
    m->setExpression("5+(3-2)*5");
    double c = m->calcul();
    //Tree* t = m->getCalcul();
    //t->afficher();
    qDebug() << "Resultat : " << c;
    delete m;
}

QTEST_MAIN(MathExp_tests)
