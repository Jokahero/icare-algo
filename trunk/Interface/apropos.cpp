#include "apropos.h"

Apropos::Apropos() : QWidget()
{
        QVBoxLayout *m_layout = new QVBoxLayout (this);
        m_texte = new QLabel ();
        m_texte->setText(tr("Work in progress ..."));
        m_layout->insertWidget(0, m_texte);

        m_close = new QPushButton(tr("&Fermer"));
        m_layout->insertWidget(1, m_close);

        setLayout(m_layout);

        QObject::connect(m_close, SIGNAL(clicked()), this, SLOT(close()));
}
