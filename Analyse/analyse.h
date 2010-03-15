#ifndef ANALYSE_H
#define ANALYSE_H

#include "Analyse_global.h"
#include "instruction.h"
#include "dictionnaire.h"
#include "expressionlogique.h"
#include "mathexp.h"

#include <QtCore/QObject>

class AnalyseSemantique;
class AnalyseSyntaxique;
class Execution;
class Glossaire;
class QFile;
template <typename T> class QList;

/** \brief Interface entre les différentes classes d'analyse et l'interface graphique.

  Singleton
*/
class Analyse : public QObject {
    Q_OBJECT

public:
    static Analyse* getInstance();

    Glossaire* getGlossaire() const;
    QList<Instruction*>* getListeInstruction() const;

    void emettreSaisie(bool pBonType);

    void setDebutGlossaire(int pNumLigne);
    void setFinGlossaire(int pNumLigne);
    void setDebutAlgo(int pNumLigne);
    void setFinAlgo(int pNumLigne);

    int getDebutGlossaire() const;
    int getFinGlossaire() const;
    int getDebutAlgo() const;
    int getFinAlgo() const;

    enum erreur {
        VariableNonDeclaree,        /*!< La variable recherchée n'a pas été déclarée. */
        VariableDejaDeclaree,       /*!< Lors de l'ajout d'une variable, une variable portant le même nom a déjà été déclarée. */
        VariableNonInitialisee,     /*!< La variable demandée n'a pas été initialisée. */
        TypeIncorrect,              /*!< La variable a été déclarée avec un type différent. */
        Syntaxe,                    /*!< Une erreur de syntaxe a été trouvée. */
        Struct,                     /*!< Une structure de contrôle n'a pas été formée correctement. */
    };

public slots:
    void lancerAnalyseSyntaxique(QFile* pFichier);
    void lancerAnalyseSemantique();
    void lancerExecution(bool pPasAPas = false);
    void transmettreSaisie(const QString& pSaisie);

    void destroy();

signals:
    void sigLancerAnalyseSyntaxique(QFile* pFichier);
    void analyseSyntaxiqueTerminee(bool pOk);
    void sigLancerAnalyseSemantique();
    void analyseSemantiqueTerminee(bool pOk);
    void sigLancerExecution(bool pPasAPas);
    void execPas();
    void execStop();
    void executionTerminee();
    void changementLigne(int pNumLigne);
    void sigSaisir(bool pBonType);
    void sigSaisie(const QString& pSaisie);
    void sigErreur(Analyse::erreur pErreur, int pNumLigne);
    void sigErreurMathematique(MathExp::erreur pErreur, int pNumLigne);
    void sigErreurLogique(ExpressionLogique::erreur pErreur, int pNumLigne);
    void sigAfficher(const QString& pChaine);

private:
    static Analyse *_instance;                      /*!< \brief Seule instance de la classe (Singleton). */
    Analyse();
    ~Analyse();

    QList<Instruction*>* m_listeInstruction;        /*!< \brief Liste des instructions extraites du code. */
    Glossaire* m_glossaire;                         /*!< \brief Glossaire où sont stockées les variables. */
    AnalyseSyntaxique* m_analyseSyntaxique;         /*!< \brief Analyseur syntaxique. */
    AnalyseSemantique* m_analyseSemantique;         /*!< \brief Analyseur sémantique. */
    Execution* m_exec;                              /*!< \brief Exécution. */
    int m_debutGlossaire;                           /*!< \brief Contient la position du début du glossaire. */
    int m_finGlossaire;                             /*!< \brief Contient la position du fin du glossaire. */
    int m_debutAlgo;                                /*!< \brief Contient la position du début de l'algorithme. */
    int m_finAlgo;                                  /*!< \brief Contient la position du fin de l'algorithme. */
};

#endif // ANALYSE_H
