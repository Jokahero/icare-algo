#ifndef GLOSSAIRE_H
#define GLOSSAIRE_H

#include <QObject>
#include <QtCore/QHash>
#include "Analyse_global.h"

/*! \brief Permet de stocker les variables du code algorithmique.
*/
class ANALYSESEMANTIQUESHARED_EXPORT Glossaire : public QObject {
    Q_OBJECT

public:
    Glossaire();
    bool existe(QString pNomVar);
    bool ajoutEntier(QString pNomVar, QString pDescription);
    bool ajoutChaine(QString pNomVar, QString pDescription);
    bool ajoutDouble(QString pNomVar, QString pDescription);

    int getValeurEntier(QString pNomVar);
    QString getValeurChaine(QString pNomVar);
    double getValeurDouble(QString pNomVar);

    void setValeurEntier(QString pNomVar, int pValeur);
    void setValeurChaine(QString pNomVar, QString pValeur);
    void setValeurDouble(QString pNomVar, double pValeur);

private:
    QHash<QString, int>* m_listeEntier;
    QHash<QString, QString>* m_listeChaine;
    QHash<QString, double>* m_listeDouble;
    QHash<QString, QString>* m_description;

signals:
    void erreur(int);
};

#endif // GLOSSAIRE_H
