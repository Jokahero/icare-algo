#include "cli.h"

#include "../Analyse/analyse.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QtCore/QStringList>

#include <iostream>
#include <cstdlib>

Cli::Cli(const QStringList& pArgs) {
    m_nomFichier = pArgs.last();
    connect(Analyse::getInstance(), SIGNAL(analyseSyntaxiqueTerminee(bool)), this, SLOT(analyseSyntaxiqueTerminee(bool)));
    connect(Analyse::getInstance(), SIGNAL(analyseSemantiqueTerminee(bool)), this, SLOT(analyseSemantiqueTerminee(bool)));
    connect(Analyse::getInstance(), SIGNAL(executionTerminee()), this, SLOT(execTerminee()));
    connect(Analyse::getInstance(), SIGNAL(sigAfficher(QString)), this, SLOT(afficher(QString)));
    connect(Analyse::getInstance(), SIGNAL(sigSaisir(bool)), this, SLOT(saisir(bool)));
    connect(this, SIGNAL(saisie(QString)), Analyse::getInstance(), SLOT(transmettreSaisie(QString)));
}

Cli::~Cli() {
    if (m_f) {
        if (m_f->isOpen())
            m_f->close();
        delete m_f;
    }
}

void Cli::exec() {
    std::cout << "Nom du fichier à interpréter : " << m_nomFichier.toStdString() << std::endl;
    m_f = new QFile(m_nomFichier);
    if (!m_f->exists()) {
        std::cerr << "Le fichier " << m_nomFichier.toStdString() << " n'existe pas." << std::endl;
        exit(1);
    }
    Analyse::getInstance()->lancerAnalyseSyntaxique(m_f);
}

void Cli::analyseSyntaxiqueTerminee(bool pOk) {
    if (pOk)
        Analyse::getInstance()->lancerAnalyseSemantique();
    else {
        std::cout << "Des erreurs ont eu lieu durant l'analyse syntaxique." << std::endl;
        exit(1);
    }
}

void Cli::analyseSemantiqueTerminee(bool pOk) {
    if (pOk)
        Analyse::getInstance()->lancerExecution(false);
    else {
        std::cout << "Des erreurs ont eu lieu durant l'analyse sémantique." << std::endl;
        exit(2);
    }
}

void Cli::execTerminee() {
    std::cout << "Exécution terminée." << std::endl;
    exit(0);
}

void Cli::afficher(const QString& pChaine) {
    std::cout << "> " << pChaine.toStdString() << std::endl;
}

void Cli::saisir(bool pTypeOk) {
    qApp->processEvents();
    std::string ret;
    if (!pTypeOk)
        std::cout << "Type incorrect." << std::endl;
    std::cin >> ret;
    emit saisie(QString::fromStdString(ret));
}
