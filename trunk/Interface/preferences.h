#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QtGui>

class Preferences : public QDialog {

    Q_OBJECT

public:
    Preferences();

private:
    QTabWidget *m_onglets;
    QWidget *m_color;

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

    QPushButton *m_annuler;
    QPushButton *m_quitter;
public slots:
    void modifierCouleur();
};

#endif // PREFERENCES_H
