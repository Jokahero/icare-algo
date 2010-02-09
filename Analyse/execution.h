#ifndef EXECUTION_H
#define EXECUTION_H

#include <QtCore/QObject>
#include "analyse.h"
#include "dictionnaire.h"

template <typename T> class QStack;
class QString;

class Execution : public QObject {
    Q_OBJECT

public:
    Execution(Analyse* pAnalyse);

private:
    Analyse* m_analyse;

    QStack<Dictionnaire::typeLigne>* m_pileStructureControle;

    QString remplacementValeursVariables(QString pChaine);

public slots:
    void lancer();

signals:
    void terminee();
    void afficher(QString);
};

#endif // EXECUTION_H
