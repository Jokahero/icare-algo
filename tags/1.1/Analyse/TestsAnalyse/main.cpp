#include "analyse_tests.h"

#include <QtCore/QTextCodec>
#include <QTest>

int main(int argc, char** argv) {
    // Réglage de l'encodage
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    Analyse_tests at;
    return QTest::qExec(&at, argc, argv);
}
