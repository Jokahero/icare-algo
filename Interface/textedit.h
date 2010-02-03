#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QtGui/QPlainTextEdit>
#include "coloration.h"

 class QPaintEvent;
 class QResizeEvent;
 class QSize;

 class lineNumberArea;

/*! \brief Zone de texte permettant d'afficher et de modifier le contenu du fichier
*/
class TextEdit : public QPlainTextEdit {
    Q_OBJECT
public:
    TextEdit();

private:
    void wheelEvent(QWheelEvent* pEvent);
    Coloration *m_color;

public:
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
     void resizeEvent(QResizeEvent *event);

 private slots:
     void updateLineNumberAreaWidth(int newBlockCount);
     void highlightCurrentLine();
     void updateLineNumberArea(const QRect &, int);

 private:
     QWidget *lineNumberArea;
     bool isLineNumberArea;
     void changerCouleur();

 public slots:
     void loadSettings();

};

 class LineNumberArea : public QWidget
 {
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
