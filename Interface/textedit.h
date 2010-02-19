#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QtGui/QPlainTextEdit>

class BarreNombres;
class Coloration;
class QPaintEvent;
class QResizeEvent;
class QSize;
class Window;

/*! \brief Zone de texte permettant d'afficher et de modifier le contenu du fichier
*/
class TextEdit : public QFrame {
    Q_OBJECT

public:
    TextEdit(Window *pParent = 0);
    ~TextEdit();

    QTextEdit *getTextEdit() const { return m_textEdit; }

public slots:
    void loadSettings();
    void changementLigne(int pNumLigne);
    void recherche(QString pRecherche);
    void remplacement(QString pRecherche, QString pRemplacement);
    void remplacerTout(QString pRecherche, QString pRemplacement);

protected slots:
    void highlightCurrentLine();

private:
    QTextEdit *m_textEdit;
    BarreNombres *m_barreNombres;
    void wheelEvent(QWheelEvent* pEvent);
    Coloration* m_color;
    void dropEvent(QDropEvent *pEvent);
    Window *m_parent;

    bool m_isLineNumberArea;
    bool m_isRetourLigne;
    int m_tailleTab;
    void changerCouleur();
};


#endif // TEXTEDIT_H
