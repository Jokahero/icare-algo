#ifndef WIDGETPLUGINS_H
#define WIDGETPLUGINS_H

#include <QtGui/QDialog>

class GestionnairePlugins;
class QCheckBox;
class QDialogButtonBox;
template <typename T> class QList;

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

public slots:
    void saveSettings();
    void accept();
    void loadSettings();

signals:
    void settingsChanged();
};

#endif // WIDGETPLUGINS_H
