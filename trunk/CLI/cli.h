#ifndef CLI_H
#define CLI_H

#include <QtCore/QObject>
#include <QtCore/QString>

class QFile;
class QStringList;

class Cli : public QObject {

    Q_OBJECT

public:
    Cli(const QStringList& pArgs);
    ~Cli();
    void    exec();

public slots:
    void    analyseSyntaxiqueTerminee(bool pOk);
    void    analyseSemantiqueTerminee(bool pOk);
    void    execTerminee();
    void    afficher(const QString& pChaine);
    void    saisir(bool pTypeOk);

signals:
    void    saisie(const QString& pChaine);

private:
    QString m_nomFichier;
    QFile*  m_f;
};

#endif // CLI_H
