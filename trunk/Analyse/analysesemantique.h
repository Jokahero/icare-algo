#ifndef ANALYSESEMANTIQUE_H
#define ANALYSESEMANTIQUE_H

#include <QObject>

class Analyse;

class AnalyseSemantique : public QObject {

    Q_OBJECT

public:
    AnalyseSemantique(Analyse* pAnalyse);

private:
    Analyse* m_analyse;
};

#endif // ANALYSESEMANTIQUE_H
