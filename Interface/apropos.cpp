#include "apropos.h"

#include <QtGui/QLabel>
#include <QtGui/QPixmap>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>


/*! \brief Constructeur. Initialise la fenêtre.
*/
Apropos::Apropos() : QWidget() {
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumSize(300,150);

    QVBoxLayout *m_layout = new QVBoxLayout (this);
    m_texte = new QLabel ();
    m_texte->setText(tr("Work in progress ..."));
    m_icone = new QLabel();
    m_image = QPixmap(":/Images/menAtWork.gif");
    m_icone->setPixmap(m_image);
    m_layout->insertWidget(1, m_texte);
    m_layout->insertWidget(0,m_icone);

    m_close = new QPushButton(tr("&Fermer"));
    m_layout->insertWidget(2, m_close);

    setLayout(m_layout);

    QObject::connect(m_close, SIGNAL(clicked()), this, SLOT(close()));
}

Apropos::~Apropos() {
    delete m_texte;
    delete m_close;
    delete m_icone;

}
