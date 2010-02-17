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
    ~Execution();

private:
    Analyse* m_analyse;

    QStack<Dictionnaire::typeLigne>* m_pileStructureControle;
    QString m_saisie;
    bool m_modifie;

    QString remplacementValeursVariables(QString pChaine);
    bool evaluationCondition(QString pVal1, QString pOp, QString pVal2);

    void execution(int pDebut = 0, int pFin = -1);

public slots:
    void lancer();
    void enregistrerSaisie(QString pSaisie);

signals:
    void terminee();
    void afficher(QString);
};

#endif // EXECUTION_H
