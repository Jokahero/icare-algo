#ifndef COLORATION_H
#define COLORATION_H

#include <QtGui>

class Coloration : public QSyntaxHighlighter
{
Q_OBJECT

public:
    Coloration(QTextEdit *pTextEdit);

private:
 struct HighlightingRule //Structure indiquant le regexp et le format du texte Ã  colorier
 {
 QRegExp pattern;
 QTextCharFormat format;
 };
 QVector<HighlightingRule> highlightingRules;

 QTextCharFormat keywordFormat; //Format des mots-clÃ©s
 QTextCharFormat commentFormat; //Format des commentaires simples

protected:
 void highlightBlock(const QString &text); //DÃ©claration en fonction protÃ©gÃ© car c'est en protÃ©gÃ© qu'elle est dÃ©clarÃ© dans sa classe parente

};

#endif // COLORATION_H
