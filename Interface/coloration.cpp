#include "coloration.h"

Coloration::Coloration(QTextEdit *textEdit) : QSyntaxHighlighter(textEdit)
{
    HighlightingRule rule;

    /*Nous indiquons une couleur et un format de police aux mots-clés.
 Nous créons ensuite une liste (stringlist, ici un QStringList) contenant les mots-clés sous forme de regexp.
 Nous faisons ensuite une boucle pour inscrire dans notre structure chaque mot-clé en regexp avec le format.
 Nous appelons ensuite une fonction faisant un petit traitement et qui appel ensuite highlightingBlock.*/
    keywordFormat.setForeground(QColor(0, 153, 255));
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;

    // ****************
    // A modifier
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
            << "\\bdouble\\b" << "\\benum\\b" ;
    // ****************

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    /*Comme ci-dessus pour les mots-clés, mais ici comme c'est des commentaires sur une ligne (donc simple),
 il n'y a pas besoin de faire un foreach ni stringList.*/
    commentFormat.setForeground(QColor(0,180,0));
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = commentFormat;
    highlightingRules.append(rule);
}

/*La fonction va rechercher le ou les mots suivant le regexp.
 Elle lui applique la couleur désiré ainsi que le format.
 Elle indique ensuite qu'elle Ã  terminé le traitement.*/
void Coloration::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);
}
