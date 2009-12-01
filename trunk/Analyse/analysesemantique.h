#ifndef ANALYSESEMANTIQUE_H
#define ANALYSESEMANTIQUE_H

#include <QObject>
#include "analyse.h"

class AnalyseSemantique : public QObject
{
public:
    AnalyseSemantique(Analyse* pAnalyse);

private:
    Analyse* m_analyse;
};

#endif // ANALYSESEMANTIQUE_H
