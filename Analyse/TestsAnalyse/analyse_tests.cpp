#include "analyse_tests.h"

void Analyse_tests::testGlossaire() {
    QVERIFY(!g->existe("Toto"));
    QVERIFY(g->ajout("Toto", 5));
    QVERIFY(g->existe("Toto"));
    QVERIFY(!g->ajout("Toto", "test"));
}

void Analyse_tests::initTestCase() {
    g = new Glossaire();
}

void Analyse_tests::cleanupTestCase() {
    delete g;
}

QTEST_MAIN(Analyse_tests)
