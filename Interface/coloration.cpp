#include "coloration.h"

#include "gestionnaireparametres.h"

#include <QtCore/QRegExp>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVector>
#include <QtGui/QColor>
#include <QtGui/QTextCharFormat>
#include <QtGui/QTextDocument>


/*! \brief Constructeur. Associe la coloration à un document.
  \param pTextDocument Document auquel associer la coloration
*/
Coloration::Coloration(QTextDocument *pTextDocument) : QSyntaxHighlighter(pTextDocument) {
    HighlightingRule type;
    HighlightingRule controle;
    HighlightingRule comment;
    HighlightingRule chaines;
    HighlightingRule borne;
    HighlightingRule numerique;

    loadSettings();

    /* Coloration des types de variables */
    // Récupération de la couleur sauvegardées dans les préférences préférences
    // Nous indiquons une couleur et un format de police aux mots-clés.
    m_typeFormat.setFontWeight(QFont::Bold);

    // Nous créons ensuite une liste contenant les mots-clés sous forme de regexp.
    QStringList typePatterns;
    typePatterns << "\\bentier\\b"
            << "\\br[ée]el" << "\\bcaract[èe]re\\b"
            << "\\bbool[ée]en\\b" << "\\bcha[îi]ne\\b";

    // Nous faisons ensuite une boucle pour inscrire dans notre structure chaque mot-clé en regexp avec le format.
    foreach (const QString &pattern, typePatterns) {
        type.pattern = QRegExp(pattern);
        type.pattern.setCaseSensitivity(Qt::CaseInsensitive);
        type.format = m_typeFormat;
        highlightingRules.append(type);
    }

    /* Coloration des structures de contrôle */
    m_structureFormat.setFontWeight(QFont::Normal);

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
        controle.format = m_structureFormat;
        highlightingRules.append(controle);
    }

    /* Coloration des bornes */
    m_borneFormat.setFontWeight(QFont::Bold);

    QStringList bornePatterns;
    bornePatterns << "\\bglossaire\\b" << "\\bd[ée]but\\b" << "\\bfin\\b";

    foreach (const QString &pattern, bornePatterns) {
        borne.pattern = QRegExp(pattern);
        borne.pattern.setCaseSensitivity(Qt::CaseInsensitive);
        borne.format = m_borneFormat;
        highlightingRules.append(borne);
    }

    /* Coloration des valeurs numériques */
    m_numeriqueFormat.setFontWeight(QFont::Normal);

    numerique.pattern = QRegExp("[0-9]+\\.?[0-9]*");
    numerique.format = m_numeriqueFormat;
    highlightingRules.append(numerique);

    /* Coloration des chaînes */
    chaines.pattern = QRegExp("\".*\"");
    chaines.format = m_chainesFormat;
    highlightingRules.append(chaines);


    /* Coloration des commentaires */

    QStringList commentPatterns;
    commentPatterns << "/\\*.*\\*/" << "//[^\n]*";
    foreach (const QString &pattern, commentPatterns) {
        comment.pattern = QRegExp(pattern);
        comment.format = m_commentFormat;
        highlightingRules.append(comment);
    }
}


/*! \brief Applique la coloration adaptée au bloc de texte courant.

  Le définit ensuite comme déjà traîté.

  \param text Texte à colorer
*/
void Coloration::highlightBlock(const QString &text) {
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


/*! \brief Charge les paramètres enregistrés dans les préférences.
*/
void Coloration::loadSettings() {
    m_typeFormat.setForeground(GestionnaireParametres::getInstance()->getCouleurTypes());;
    m_structureFormat.setForeground(GestionnaireParametres::getInstance()->getCouleurStructures());
    m_commentFormat.setForeground(GestionnaireParametres::getInstance()->getCouleurCommentaires());
    m_chainesFormat.setForeground(GestionnaireParametres::getInstance()->getCouleurChaines());
    m_borneFormat.setForeground(GestionnaireParametres::getInstance()->getCouleurBornes());
    m_numeriqueFormat.setForeground(GestionnaireParametres::getInstance()->getCouleurNombres());
}

