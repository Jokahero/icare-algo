#ifndef ANALYSE_TESTS_H
#define ANALYSE_TESTS_H

#include <QtCore/QObject>

/*! \brief Tests du module d'analyses.

  Teste \em Glossaire.
*/
class Analyse_tests : public QObject {
    Q_OBJECT

private slots:
    void testGlossaire();
    void testArbre();
    void testMathExp();
    void testMathExp_data();
    void testExpressionLogique();
    void testExpressionLogique_data();
    void cleanupTestCase();
};

#endif // ANALYSE_TESTS_H
