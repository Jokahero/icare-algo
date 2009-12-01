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

 QTextCharFormat typeFormat; //Format des types
 QTextCharFormat structureFormat; // Format des structures de controle
 QTextCharFormat commentFormat; //Format des commentaires simples

protected:
 void highlightBlock(const QString &text); //Déclaration en fonction protégé car c'est en protégé qu'elle est déclaré dans sa classe parente

};

#endif // COLORATION_H
