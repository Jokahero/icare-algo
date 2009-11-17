#ifndef ANALYSE_TESTS_H
#define ANALYSE_TESTS_H

#include <QObject>
#include <QtCore>
#include <QtTest>
#include "../glossaire.h"

/*! \brief Tests du module d'analyses.

  Teste \em Glossaire.
*/
class Analyse_tests : public QObject {
    Q_OBJECT
private slots:
    void initTestCase();
    void testGlossaire();
    void cleanupTestCase();

private:
    Glossaire* g;
};

#endif // ANALYSE_TESTS_H
