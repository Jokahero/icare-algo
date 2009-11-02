#ifndef WIDGETEXEC_H
#define WIDGETEXEC_H

#include <QtCore>
#include <QtGui>

#include "../../Interface/plugininterface.h"

/*! \brief Widget affichant le résultat des analyses, les sorties d'exécutions et permet la saisie lors des exécutions.
*/
class WidgetExec : public QObject, PluginInterface {

    Q_OBJECT
    Q_INTERFACES(PluginInterface)

public:
    WidgetExec();
    QString getNom();
    QWidget* getWidget();

private slots:
    void ajouterTexte(QString pTexte);
    void effacerTexte();
    void remplacerTexte(QString pTexte);

private:
    QTextEdit* m_textEdit;
};

#endif // WIDGETEXEC_H
