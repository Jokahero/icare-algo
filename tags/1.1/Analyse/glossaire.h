#ifndef GLOSSAIRE_H
#define GLOSSAIRE_H

#include "analyse.h"

#include <QtCore/QObject>

template <typename T, typename U> class QHash;

/*! \brief Permet de stocker les variables du code algorithmique.
*/
class Glossaire : public QObject {
    Q_OBJECT

public:
    Glossaire();
    ~Glossaire();

    bool existe(const QString& pNomVar) const;
    bool ajoutBool(const QString& pNomVar, const QString& pDescription, int pNumLigne = 0);
    bool ajoutEntier(const QString& pNomVar, const QString& pDescription, int pNumLigne = 0);
    bool ajoutChaine(const QString& pNomVar, const QString& pDescription, int pNumLigne = 0);
    bool ajoutReel(const QString& pNomVar, const QString& pDescription, int pNumLigne = 0);

    bool getValeurBool(const QString& pNomVar) const;
    int getValeurEntier(const QString& pNomVar) const;
    QString getValeurChaine(const QString& pNomVar) const;
    double getValeurReel(const QString& pNomVar) const;

    QString getValeur(const QString& pNomVar) const;

    void setValeurBool(const QString& pNomVar, bool pValeur);
    void setValeurEntier(const QString& pNomVar, int pValeur);
    void setValeurChaine(const QString& pNomVar, const QString& pValeur);
    void setValeurReel(const QString& pNomVar, double pValeur);

    bool setValeur(const QString& pNomVar, const QString& pValeur);

    QStringList getListeVariables() const;
    
    void reinit();


private:
    QHash<QString, bool>* m_listeBools;                      /*! < \brief Stocke les booléens. */
    QHash<QString, int>* m_listeEntier;                      /*! < \brief Stocke les variables entières. */
    QHash<QString, QString>* m_listeChaine;                  /*! < \brief Stocke les chaînes de caractères. */
    QHash<QString, double>* m_listeReel;                     /*! < \brief Stocke les variables à virgules. */
    QHash<QString, QString>* m_description;                  /*! < \brief Stocke les descriptions de toutes les variables. */
    QHash<QString, bool>* m_initialisations;                 /*! < \brief Stocke l'étât d'initialisation des variables. */

signals:
    void erreur(Analyse::erreur pErreur, int pNumLigne = 0) const;
    void variableAjoutee(const QString& pNomVar, const QString& pType, const QString& pDescription) const;
    void variableModifiee(const QString& pNomVar, const QString& pValeur) const;
    void sigReinit() const;
};

#endif // GLOSSAIRE_H
