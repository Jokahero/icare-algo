#ifndef GLOSSAIRE_H
#define GLOSSAIRE_H

#include <QObject>
#include <QtCore/QHash>

/*! \brief Permet de stocker les variables du code algorithmique.
*/
class Glossaire : public QObject {
public:
    Glossaire();
    bool existe(QString pNomVar);
    bool ajout(QString pNomVar, int pValeur);
    bool ajout(QString pNomVar, QString pValeur);
    bool ajout(QString pNomVar, double pValeur);

private:
    QHash<QString, int>* m_listeInt;
    QHash<QString, QString>* m_listeChaine;
    QHash<QString, double>* m_listeDouble;
};

#endif // GLOSSAIRE_H
