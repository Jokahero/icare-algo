#ifndef WIDGETPLUGINS_H
#define WIDGETPLUGINS_H

#include <QtGui/QDialog>

class GestionnairePlugins;
class QCheckBox;
class QDialogButtonBox;
class QLabel;
template <typename T> class QList;


/*! \brief Fenêtre affichant la liste des plugins disponnibles et permettant à l'utilisateur de choisir lesquels il veut activer.
*/
class WidgetPlugins : public QDialog {
    Q_OBJECT

public:
    WidgetPlugins();
    ~WidgetPlugins();
    GestionnairePlugins *getGestionnairePlugins();

private:
    GestionnairePlugins *m_gestionnairePlugins;
    QDialogButtonBox *m_buttonBox;
    QList<QCheckBox*> *m_listeCheck;
    QLabel *m_infoLabel;

public slots:
    void saveSettings();
    void accept();
    void loadSettings();

signals:
    void settingsChanged();
};

#endif // WIDGETPLUGINS_H
