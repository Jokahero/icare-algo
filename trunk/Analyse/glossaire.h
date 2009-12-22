#ifndef GLOSSAIRE_H
#define GLOSSAIRE_H

#include <QObject>
#include <QtCore/QHash>

#include "analyse.h"

/*! \brief Permet de stocker les variables du code algorithmique.
*/
class Glossaire : public QObject {
	
    Q_OBJECT

public:
    Glossaire();
    bool existe(QString pNomVar);
    bool ajoutEntier(QString pNomVar, QString pDescription, int pNumLigne = 0);
    bool ajoutChaine(QString pNomVar, QString pDescription, int pNumLigne = 0);
    bool ajoutReel(QString pNomVar, QString pDescription, int pNumLigne = 0);

    int getValeurEntier(QString pNomVar);
    QString getValeurChaine(QString pNomVar);
    double getValeurReel(QString pNomVar);

    void setValeurEntier(QString pNomVar, int pValeur);
    void setValeurChaine(QString pNomVar, QString pValeur);
    void setValeurReel(QString pNomVar, double pValeur);

    QStringList getListeVariables();
    
    void reinit();


private:
    QHash<QString, int>* m_listeEntier;                      /*!<\brief Stocke les variables entieres. */
    QHash<QString, QString>* m_listeChaine;                  /*!<\brief Stocke les chaines de caracteres. */
    QHash<QString, double>* m_listeReel;                     /*!<\brief Stocke les variables a virgules. */
    QHash<QString, QString>* m_description;                  /*!<\brief Stocke les descriptions de toutes les variables. */

signals:
    void erreur(Analyse::erreur pErreur, int pNumLigne = 0);
    void variableAjoutee(QString pNomVar, QString pType, QString pDescription);
    void variableModifiee(QString pNomVar, QString pValeur);
    void sigReinit();
};

#endif // GLOSSAIRE_H
