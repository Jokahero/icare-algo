#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QtGui/QFrame>
#include <QtGui/QTextEdit>

class BarreNombres;
class Coloration;
class QPaintEvent;
class QResizeEvent;
class QSize;
class Window;

class TextEdit;

class DropableTextEdit : public QTextEdit {
    Q_OBJECT

public:
    DropableTextEdit(TextEdit *pParent = 0);

private:
    void dropEvent(QDropEvent *pEvent);
    TextEdit *m_parent;
};

/*! \brief Zone de texte permettant d'afficher et de modifier le contenu du fichier
*/
class TextEdit : public QFrame {
    Q_OBJECT

public:
    TextEdit(Window *pParent = 0);
    ~TextEdit();

    DropableTextEdit *getTextEdit() const { return m_textEdit; }
    Window *getParent() const { return m_parent; }

public slots:
    void loadSettings();
    void changementLigne(int pNumLigne);
    void recherche(QString pRecherche);
    void remplacement(QString pRecherche, QString pRemplacement);
    void remplacerTout(QString pRecherche, QString pRemplacement);
    void ajouterTexte(QString pTexte);

protected slots:
    void highlightCurrentLine();

private:
    DropableTextEdit *m_textEdit;
    BarreNombres *m_barreNombres;
    void wheelEvent(QWheelEvent* pEvent);
    Coloration* m_color;
    Window *m_parent;

    bool m_isLineNumberArea;
    bool m_isRetourLigne;
    int m_tailleTab;
    void changerCouleur();
};


#endif // TEXTEDIT_H
