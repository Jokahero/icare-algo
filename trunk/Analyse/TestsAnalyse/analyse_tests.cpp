#include "analyse_tests.h"

void Analyse_tests::testGlossaire() {
    QVERIFY(!g->existe("Toto"));
    QVERIFY(g->ajoutEntier("Toto", "Variable de test"));
    QVERIFY(g->existe("Toto"));
    QVERIFY(!g->ajoutChaine("Toto", "test"));
    QVERIFY(g->getValeurChaine("Toto") == QString::null);
    QVERIFY(g->getValeurEntier("Toto") == 0);
    g->setValeurEntier("Toto", 42);
    QVERIFY(g->getValeurEntier("Toto") == 42);
}

void Analyse_tests::initTestCase() {
    g = new Glossaire();
}

void Analyse_tests::cleanupTestCase() {
    delete g;
}

QTEST_MAIN(Analyse_tests)
