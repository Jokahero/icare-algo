#ifndef ANALYSESEMANTIQUE_H
#define ANALYSESEMANTIQUE_H

#include <QObject>
#include "dictionnaire.h"
#include "analyse.h"

template <typename T> class QStack;

class AnalyseSemantique : public QObject {

    Q_OBJECT

public:
    AnalyseSemantique(Analyse* pAnalyse);

private:
    Analyse* m_analyse;

    QStack<Dictionnaire::typeLigne>* m_pileStructureControle;

    void verifStruct();

public slots:
    void lancer();

signals:
    void terminee();
    void erreur(Analyse::erreur pErreur, int pNumLigne);
};

#endif // ANALYSESEMANTIQUE_H
