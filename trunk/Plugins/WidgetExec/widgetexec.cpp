#include "widgetexec.h"

/*! \brief Constructeur. Initialise le widget avec un QTextEdit.
*/
WidgetExec::WidgetExec() {
    m_dockWidget = new QDockWidget;
    QWidget* tmp = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(tmp);
    m_textEdit = new QTextEdit;
    layout->addWidget(m_textEdit);
    m_textEdit->setReadOnly(true);
    tmp->setLayout(layout);
    m_dockWidget->setWidget(tmp);
    m_dockWidget->setWindowTitle(getNom());
}

/*! \brief Ajoute le texte indiqué à la suite du texte présent.

  \param pTexte Texte à ajouter.
*/
void WidgetExec::ajouterTexte(QString pTexte) {
    m_textEdit->append(pTexte);
}

/*! \brief Efface le contenu du widget.

*/
void WidgetExec::effacerTexte() {
    m_textEdit->clear();
}

/*! \brief Remplace le texte présent du widget.

  Appelle successivement effacerTexte et ajouterTexte avec le texte passé en paramètre.
  \param pTexte Texte à affecter au widget.
*/
void WidgetExec::remplacerTexte(QString pTexte) {
    effacerTexte();
    ajouterTexte(pTexte);
}

QString WidgetExec::getNom() {
    return QString("WidgetExec");
}

QDockWidget* WidgetExec::getDockWidget() {
    return m_dockWidget;
}

Q_EXPORT_PLUGIN2(widgetexec, WidgetExec);
