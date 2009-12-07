#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QtGui>

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
    QPushButton *m_commentairesBouton;

    QLabel *m_bornesLabel;
    QPushButton *m_bornesBouton;

    QLabel *m_structuresLabel;
    QPushButton *m_structuresBouton;

    QLabel *m_numeriqueLabel;
    QPushButton *m_numeriqueBouton;

    QLabel *m_typeLabel;
    QPushButton *m_typeBouton;

    /* Pour les boutons Ok et Annuler */
    QDialogButtonBox *m_buttonBox;

public slots:
    void modifierCouleur();
};

#endif // PREFERENCES_H
