#ifndef WIDGETPLUGINS_H
#define WIDGETPLUGINS_H

#include <QtGui/QDialog>

class QCheckBox;
class QDialogButtonBox;

class WidgetPlugins : public QDialog
{
    Q_OBJECT

public:
    WidgetPlugins();

private:

    QCheckBox *m_glossaire;
    QCheckBox *m_resultat;

    QDialogButtonBox *m_buttonBox;

public slots:
    void saveSettings();
    void accept();
    void loadSettings();

signals:
    void settingsChanged();
};

#endif // WIDGETPLUGINS_H
