#include "apropos.h"

#include <QtCore/QDebug>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QPalette>
#include <QtGui/QPixmap>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>


/*! \brief Constructeur. Initialise la fenêtre.
*/
Apropos::Apropos() : QDialog() {
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumSize(300,150);
    setWindowTitle("À propos de Icare");

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    QVBoxLayout *infosLayout = new QVBoxLayout ();
    m_version = new QLabel();
    m_version->setText(tr("<b>Icare - Version 1.0</b>"));
    m_Qt = new QLabel();
    m_Qt->setText(tr("Basé sur Qt 4.6.2"));
    m_noms = new QLabel ();
    m_noms->setText(tr("Développé par:\n- Buffon Nicolas\n- Desbeaux Vincent\n- Plano-Lesay Marc\n- Ramondou Clémence"));
    m_site = new QLabel();
    m_site->setText("<a href=\"http://icare-algo.ath.cx\">http://icare-algo.ath.cx</a>");
    m_site->setOpenExternalLinks(true);
    m_icone = new QLabel();
    m_icone->setPixmap(QPixmap(":/Images/icare.png").scaled(170,130.75));
    infosLayout->addWidget(m_version);
    infosLayout->addWidget(m_Qt);
    infosLayout->addWidget(m_noms);
    infosLayout->addWidget(m_site);

    QHBoxLayout *layoutG = new QHBoxLayout();
    layoutG->addWidget(m_icone);
    layoutG->addLayout(infosLayout);

    QVBoxLayout *layoutP = new QVBoxLayout();
    layoutP->addLayout(layoutG);
    layoutP->addWidget(m_buttonBox);

    setLayout(layoutP);

    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
}

Apropos::~Apropos() {
    delete m_noms;
    delete m_icone;
    delete m_version;
    delete m_buttonBox;
}
