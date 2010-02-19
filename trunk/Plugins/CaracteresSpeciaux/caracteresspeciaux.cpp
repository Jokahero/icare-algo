#include "caracteresspeciaux.h"

#include <QtCore/QSettings>
#include <QtCore/QString>

/*! \brief Constructeur. Initialise le widget avec un QTextEdit.
*/
CaracteresSpeciaux::CaracteresSpeciaux() {
    m_menu = new QMenu(tr("Caractères spéciaux"));
    m_menuComp = new QMenu(tr("Comparaisons"), m_menu);
    m_menuAff = new QMenu(tr("Affectations"), m_menu);

    m_menuComp->addAction(QString(QChar(0x2260)), this, SLOT(ajoutTexte()));
    m_menuComp->addAction(QString(QChar(0x2264)), this, SLOT(ajoutTexte()));
    m_menuComp->addAction(QString(QChar(0x2265)), this, SLOT(ajoutTexte()));

    m_menuAff->addAction(QString(QChar(0x2190)), this, SLOT(ajoutTexte()));

    m_menu->addMenu(m_menuAff);
    m_menu->addMenu(m_menuComp);
}

CaracteresSpeciaux::~CaracteresSpeciaux() {
    delete m_menu;
}

QString CaracteresSpeciaux::getNom() {
    return QString(tr("Caractères spéciaux"));
}

QMenu* CaracteresSpeciaux::getMenu() {
    return m_menu;
}

void CaracteresSpeciaux::ajoutTexte() {
    emit ajouterTexte(((QAction*)sender())->text());
}

Q_EXPORT_PLUGIN2(caracteresspeciaux, CaracteresSpeciaux);
