#include "fenetreaide.h"

#include <QtCore/QFile>
#include <QtCore/QTextStream>

FenetreAide::FenetreAide(QWidget* pParent) : QWebView(pParent) {
    setAttribute(Qt::WA_DeleteOnClose);
    load(QUrl("qrc:/Aide/aide.html"));

    setWindowTitle(tr("Aide - Icare"));
}
