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

private:
    Analyse* m_analyse;                                             /*!< \brief Pointeur vers l'instance d'analyse. */

    QString m_saisie;                                               /*!< \brief Chaîne contenant la dernière saisie de l'utilisateur. */
    bool m_modifie;                                                 /*!< \brief Booléen permettant de savoir si la saisie a été modifiée ou non. */
    bool m_stop;                                                    /*!< \brief Booléen indiquant si l'utilisateur a demandé une interruption de l'exécution. */

    QString remplacementValeursVariables(const QString& pChaine);
    QString calcul(const QString& pChaine, int pNumLigne);
    bool evaluationCondition(const QString& pCond, int pNumLigne);

    void execution(bool pPasAPas, int pDebut = 0, int pFin = -1);

    void waitForSignal(QObject* pObj, const char* pSig);

public slots:
    void lancer(bool pPasAPas = false);
    //void pas();
    void stop();
    void enregistrerSaisie(const QString& pSaisie);

signals:
    void terminee();
    void afficher(QString);
    void erreurMathematique(MathExp::erreur, int);
    void erreurLogique(ExpressionLogique::erreur, int);
    void changementLigne(int pNumLigne);
};

#endif // EXECUTION_H
