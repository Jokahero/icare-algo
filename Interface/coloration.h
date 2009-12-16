#ifndef COLORATION_H
#define COLORATION_H

#include <QtGui>
#include <QtCore>

class Coloration : public QSyntaxHighlighter
{
Q_OBJECT

public:
    Coloration(QTextDocument *pTextDocument);

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
 QTextCharFormat borneFormat; //  Format des bornes du code
 QTextCharFormat numeriqueFormat; // Format des valeurs numériques

 QColor couleur;

protected:
 void highlightBlock(const QString &text); //Déclaration en fonction protégé car c'est en protégé qu'elle est déclaré dans sa classe parente

 public slots:
    void loadSettings();
};

#endif // COLORATION_H
