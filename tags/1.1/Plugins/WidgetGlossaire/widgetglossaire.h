#ifndef WIDGETGLOSSAIRE_H
#define WIDGETGLOSSAIRE_H

#include "../../Interface/plugininterface.h"

class QDockWidget;
class QModelIndex;
class QPushButton;
class QStandardItemModel;
class QString;
class QTableView;
class QTableWidget;

/*! \brief Widget affichant la liste des variables.

  Affiche leurs noms, types et descriptions.
*/
class WidgetGlossaire : public PluginInterface {

    Q_OBJECT
    Q_INTERFACES(PluginInterface)

public:
    WidgetGlossaire();
    QString getNom();
    QDockWidget* getDockWidget();

public slots:
    void variableAjoutee(QString pNomVar, QString pType, QString pDescription, QString pValeur="", bool user=false);
    void variableModifiee(QString pNomVar, QString pValeur, QString pType="", QString pDesc="", bool user=false);
    void reinitialisationGlossaire();
    
    void afficherMenuContextuel(const QPoint& pos);

private:
    QDockWidget* m_dockWidget;
    QTableWidget* m_tableau;

    QStandardItemModel *m_modeleGlossaire;
    QTableView *m_vueGlossaire;

    QPushButton* m_addVariable;
    QPushButton* m_delVariable;

private slots:
    void sauvegarderPosition(Qt::DockWidgetArea pPos);
    void sauvegarderEtat(bool pEtat);

    void supprimerVariable();
    void ajouterVariable();
    void modifierVariable();

signals:
    void enleverVariable(QString pLine);
    void ajouterVariable(QString pLine);
};

#endif // WIDGETGLOSSAIRE_H
