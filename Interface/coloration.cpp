#include "coloration.h"

Coloration::Coloration(QTextEdit *textEdit) : QSyntaxHighlighter(textEdit)
{
    HighlightingRule type;
    HighlightingRule controle;
    HighlightingRule comment;

    /* Coloration des types de variables */
    // Nous indiquons une couleur et un format de police aux mots-clés.
    typeFormat.setForeground(QColor(0, 0, 255));
    typeFormat.setFontWeight(QFont::Bold);

    // Nous créons ensuite une liste contenant les mots-clés sous forme de regexp.
    QStringList typePatterns;
    typePatterns << "\\bentier\\b"
            << "\\br[ée]el" << "\\bcaract[èe]re\\b"
            << "\\bbool[ée]en\\b" << "\\bcha[îi]ne\\b";

    // Nous faisons ensuite une boucle pour inscrire dans notre structure chaque mot-clé en regexp avec le format.
    foreach (const QString &pattern, typePatterns) {
        type.pattern = QRegExp(pattern);
        type.pattern.setCaseSensitivity(Qt::CaseInsensitive);
        type.format = typeFormat;
        highlightingRules.append(type);
    }

    /* Coloration des structures de contrôle */
    structureFormat.setForeground(QColor(255, 165, 00));
    structureFormat.setFontWeight(QFont::Normal);

    QStringList structurePatterns;
    structurePatterns << "\\bsi\\b" << "\\balors\\b"
            << "\\bsinon\\b" << "\\bfinsi\\b";

    foreach (const QString &pattern, structurePatterns) {
        controle.pattern = QRegExp(pattern);
        controle.pattern.setCaseSensitivity(Qt::CaseInsensitive);
        controle.format = structureFormat;
        highlightingRules.append(controle);
    }


    /* Coloration des commentaires */
    commentFormat.setForeground(QColor(0,180,0));

    QStringList commentPatterns;
    commentPatterns << "/\\*.*\\*/" << "//[^\n]*";
    foreach (const QString &pattern, commentPatterns) {
        comment.pattern = QRegExp(pattern);
        comment.format = commentFormat;
        highlightingRules.append(comment);
    }
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
