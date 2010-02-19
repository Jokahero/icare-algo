#ifndef COLORATION_H
#define COLORATION_H

#include <QtGui/QSyntaxHighlighter>

class QColor;
class QRegExp;
class QString;
class QTextCharFormat;
template <typename T> class QVector;

/*! \brief Classe colorant l'algorithme en fonction de la syntaxe
*/
class Coloration : public QSyntaxHighlighter {
    Q_OBJECT

public:
    Coloration(QTextDocument *pTextDocument);

private:
    struct HighlightingRule { /*!< \brief Structure indiquant le regexp et le format du texte à colorier*/
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat typeFormat; /*!< \brief Format des types*/
    QTextCharFormat structureFormat; /*!< \brief Format des structures de controle*/
    QTextCharFormat commentFormat; /*!< \brief Format des commentaires simples*/
    QTextCharFormat borneFormat; /*!< \brief Format des bornes du code*/
    QTextCharFormat numeriqueFormat; /*!< \brief Format des valeurs numériques*/

    QColor couleur;

protected:
    void highlightBlock(const QString &text); //Déclaration en fonction protégé car c'est en protégé qu'elle est déclaré dans sa classe parente

public slots:
    void loadSettings();
};

#endif // COLORATION_H
