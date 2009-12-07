#include "preferences.h"

Preferences::Preferences() : QWidget()
{
    QFormLayout *layout = new QFormLayout();

    commentairesLabel = new QLabel(tr("Commentaires"));
    commentairesBouton = new QPushButton(tr("Modifier"));
}
