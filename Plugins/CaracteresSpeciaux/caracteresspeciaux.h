#ifndef CARACTERESSPECIAUX_H
#define CARACTERESSPECIAUX_H

#include "../../Interface/plugininterface.h"

class QDockWidget;
class QString;
class QTableWidget;

/*! \brief Plugin ajoutant un menu permettant l'ajout rapide de différents caractères spéciaux
*/
class CaracteresSpeciaux : public PluginInterface {

    Q_OBJECT
    Q_INTERFACES(PluginInterface)

public:
    CaracteresSpeciaux();
    ~CaracteresSpeciaux();

    QString getNom();
    QMenu *getMenu();

signals:
    void ajouterTexte(QString pTexte);

private slots:
    void ajoutTexte();

private:
    QMenu* m_menu;
    QMenu* m_menuComp;
    QMenu* m_menuAff;
};

#endif // WIDGETGLOSSAIRE_H
