#ifndef RECHERCHE_H
#define RECHERCHE_H

#include <QtGui/QDialog>

class QLabel;
class QLineEdit;
class QPushButton;
class QCheckBox;


/*! \brief Fenêtre de recherche/remplacement.

  \todo Refaire la mise en page, probablement avec des onglets.
*/
class Recherche : public QDialog {
    Q_OBJECT

public:
    Recherche(QWidget *pParent = 0);
    ~Recherche();

public slots:
    void plus(bool pVisible);
    void rec();
    void rem();

private:
    QLabel* m_rechercherLa;
    QLineEdit* m_rechercherLe;
    QLabel* m_remplacerLa;
    QLineEdit* m_remplacerLe;
    QPushButton* m_rechercher;
    QPushButton* m_fermer;
    QPushButton* m_plus;
    QPushButton* m_remplacerTout;
    // Options de recherche
    QCheckBox *m_caseSensitive;
    QCheckBox *m_regExp;
    QCheckBox *m_motEntier;
    QCheckBox *m_debutMot;


private slots:
    void recherche();
    void remplacerTout();

signals:
    void recherche(QString);
    void remplacement(QString, QString);
    void remplacerTout(QString, QString);
};

#endif // RECHERCHE_H
