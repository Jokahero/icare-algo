#include "cli.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QLibraryInfo>
#include <QtCore/QLocale>
#include <QtCore/QStringList>
#include <QtCore/QTextCodec>
#include <QtCore/QTranslator>

#include <iostream>

/*! \brief Point d'entrée. Lit le fichier passé en paramètre et l'interprète.

  \param argc Nombre d'arguments
  \param argv Arguments
  \return Code de retour système
*/
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QCoreApplication::setOrganizationName("IUT Blagnac");
    QCoreApplication::setOrganizationDomain("code.google.com/p/icare-algo");
    QCoreApplication::setApplicationName("Icare");

    // Réglage de l'encodage
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    // Application de la traduction
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    // De l'application elle même
    translator.load(QString("icare-cli_") + locale);
    a.installTranslator(&translator);
    // Et de Qt
    if (translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        a.installTranslator(&translator);
    else {
        translator.load(QString("qt_") + locale);
        a.installTranslator(&translator);
    }

    // Vérification des paramètres
    if (a.arguments().size() < 2) {
        std::cerr << "Usage : " << argv[0] << " [options] algorithme" << std::endl;
        return 1;
    } else {
        Cli c(a.arguments());
        c.exec();
    }

    return a.exec();
}
