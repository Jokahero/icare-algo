#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QtGui/QDialog>

class BoutonCouleur;
class QCheckBox;
class QColor;
class QDialogButtonBox;
class QLabel;
class QSpinBox;
class QString;
class QTabWidget;
class QWidget;


/*! \brief Fenêtre de préférences.
*/
class Preferences : public QDialog {
    Q_OBJECT

public:
    Preferences();

private:
    QTabWidget *m_onglets;

    /* Onglet des préférences de la coloration syntaxique */
    QWidget *m_color; // C'est le widget qui sera affiché dans l'onglet

    /* Le widget m_color contiendra ces éléments */
    QLabel *m_commentairesLabel;
    BoutonCouleur *m_commentairesBouton;

    QLabel *m_chainesLabel;
    BoutonCouleur *m_chainesBouton;

    QLabel *m_bornesLabel;
    BoutonCouleur *m_bornesBouton;

    QLabel *m_structuresLabel;
    BoutonCouleur *m_structuresBouton;

    QLabel *m_numeriqueLabel;
    BoutonCouleur *m_numeriqueBouton;

    QLabel *m_typeLabel;
    BoutonCouleur *m_typeBouton;

    /* Onglet des préférences de la zone d'édition */
    QWidget *m_edit;

    /* Le widget m_color contiendra ces éléments */
    QCheckBox *m_numerotation;
    QCheckBox *m_retourLigne;
    QSpinBox *m_tailleTab;
    BoutonCouleur *m_surligneBouton;

    /* Pour les boutons Ok et Annuler */
    QDialogButtonBox *m_buttonBox;

public slots:
    void modifierCouleur();
    void changeSettings();
    void loadSettings();
    void accept();

signals:
    void settingsChanged();
};

#endif // PREFERENCES_H
