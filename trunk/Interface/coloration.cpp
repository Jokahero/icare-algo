#include "coloration.h"

#include <QtCore/QDebug>
#include <QtCore/QRegExp>
#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVector>
#include <QtGui/QColor>
#include <QtGui/QTextCharFormat>
#include <QtGui/QTextDocument>

Coloration::Coloration(QTextDocument *pTextDocument) : QSyntaxHighlighter(pTextDocument) {
    HighlightingRule type;
    HighlightingRule controle;
    HighlightingRule comment;
    HighlightingRule borne;
    HighlightingRule numerique;

    loadSettings();

    /* Coloration des types de variables */
    // Récupération de la couleur sauvegardées dans les préférences préférences
    // Nous indiquons une couleur et un format de police aux mots-clés.
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
    structureFormat.setFontWeight(QFont::Normal);

    QStringList structurePatterns;
    structurePatterns << "\\bsi\\b" << "\\balors\\b"
            << "\\bsinon\\b" << "\\bfinsi\\b" << "\\bselon\\b"
            << "\\bcas\\b" << "\\bd[ée]faut\\b" << "\\bfinselon\\b"
            << "\\btantque\\b" << "\\bfaire\\b" << "\\bfintantque\\b"
            << "\\br[ée]p[ée]ter\\b" << "\\bjusqu'?[àa]\\b" << "\\bpour\\b"
            << "\\bde\\b" << "\\b[àa]\\b" <<  "\\bfinpour\\b";

    foreach (const QString &pattern, structurePatterns) {
        controle.pattern = QRegExp(pattern);
        controle.pattern.setCaseSensitivity(Qt::CaseInsensitive);
        controle.format = structureFormat;
        highlightingRules.append(controle);
    }

    /* Coloration des commentaires et des chaînes*/

    QStringList commentPatterns;
    commentPatterns << "/\\*.*\\*/" << "//[^\n]*" << "\".*\"";
    foreach (const QString &pattern, commentPatterns) {
        comment.pattern = QRegExp(pattern);
        comment.format = commentFormat;
        highlightingRules.append(comment);
    }

    /* Coloration des bornes */
    borneFormat.setFontWeight(QFont::Bold);

    QStringList bornePatterns;
    bornePatterns << "\\bglossaire\\b" << "\\bd[ée]but\\b" << "\\bfin\\b";

    foreach (const QString &pattern, bornePatterns) {
        borne.pattern = QRegExp(pattern);
        borne.pattern.setCaseSensitivity(Qt::CaseInsensitive);
        borne.format = borneFormat;
        highlightingRules.append(borne);
    }

    /* Coloration des valeurs numériques */
    numeriqueFormat.setFontWeight(QFont::Normal);

    numerique.pattern = QRegExp("[0-9]+\\.?[0-9]*");
    numerique.format = numeriqueFormat;
    highlightingRules.append(numerique);
}

/*La fonction va rechercher le ou les mots suivant le regexp.
 Elle lui applique la couleur désiré ainsi que le format.
 Elle indique ensuite qu'elle a terminé le traitement.*/
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

void Coloration::loadSettings() {
    QSettings settings;
    settings.sync();
    couleur.setNamedColor(settings.value("CouleurTypes").toString());
    typeFormat.setForeground(couleur);
    couleur.setNamedColor(settings.value("CouleurStructures").toString());
    structureFormat.setForeground(couleur);
    couleur.setNamedColor(settings.value("CouleurCommentaires").toString());
    commentFormat.setForeground(couleur);
    couleur.setNamedColor(settings.value("CouleurBornes").toString());
    borneFormat.setForeground(couleur);
    couleur.setNamedColor(settings.value("CouleurNombres").toString());
    numeriqueFormat.setForeground(couleur);
}

