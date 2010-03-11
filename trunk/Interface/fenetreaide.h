#ifndef FENETREAIDE_H
#define FENETREAIDE_H

#include <QtWebKit/QWebView>

class QWidget;

class FenetreAide : public QWebView {
public:
    FenetreAide(QWidget* pParent = 0);
};

#endif // FENETREAIDE_H
