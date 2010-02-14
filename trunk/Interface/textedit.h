#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QtGui/QPlainTextEdit>

class Coloration;
class lineNumberArea;
class QPaintEvent;
class QResizeEvent;
class QSize;
class Window;


/*! \brief Zone de texte permettant d'afficher et de modifier le contenu du fichier
*/
class TextEdit : public QPlainTextEdit {
    Q_OBJECT
public:
    TextEdit(Window* parent);
    ~TextEdit();

private:
    void wheelEvent(QWheelEvent* pEvent);
    Coloration* m_color;

public:
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget* m_lineNumberArea;
    bool m_isLineNumberArea;
    bool m_isRetourLigne;
    int m_tailleTab;
    void changerCouleur();
    Window* m_parent;

public slots:
    void loadSettings();
    void changementLigne(int pNumLigne);
    void recherche(QString pRecherche);
    void remplacement(QString pRecherche, QString pRemplacement);
    void remplacerTout(QString pRecherche, QString pRemplacement);

};

class LineNumberArea : public QWidget {
public:
    LineNumberArea(TextEdit *editor) : QWidget(editor) {
        m_textEdit = editor;
    }

    QSize sizeHint() const {
        return QSize(m_textEdit->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        m_textEdit->lineNumberAreaPaintEvent(event);
    }

private:
    TextEdit *m_textEdit;
};

#endif // TEXTEDIT_H
