#ifndef EXECUTION_H
#define EXECUTION_H

#include <QtCore/QObject>
#include "analyse.h"
#include "dictionnaire.h"
#include "expressionlogique.h"
#include "mathexp.h"

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
    bool m_stop;

    QString remplacementValeursVariables(QString pChaine, int pNumLigne);
    bool evaluationCondition(QString pVal1, QString pOp, QString pVal2, int pNumLigne);

    void execution(bool pPasAPas, int pDebut = 0, int pFin = -1);

    void waitForSignal(QObject* pObj, const char* pSig);

public slots:
    void lancer(bool pPasAPas = false);
    void pas();
    void stop();
    void enregistrerSaisie(QString pSaisie);

signals:
    void terminee();
    void afficher(QString);
    void erreurMathematique(MathExp::erreur, int);
    void erreurLogique(ExpressionLogique::erreur, int);
    void changementLigne(int pNumLigne);
};

#endif // EXECUTION_H
