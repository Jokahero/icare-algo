#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QtGui>

class Preferences : public QWidget
{
public:
    Preferences();

private:
    QLabel *commentairesLabel;
    QPushButton *commentairesBouton;
};

#endif // PREFERENCES_H
