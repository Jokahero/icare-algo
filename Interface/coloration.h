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

    QTextCharFormat m_typeFormat; /*!< \brief Format des types*/
    QTextCharFormat m_structureFormat; /*!< \brief Format des structures de controle*/
    QTextCharFormat m_commentFormat; /*!< \brief Format des commentaires simples*/
    QTextCharFormat m_chainesFormat; /*! < \brief Format des chînes de caractères*/
    QTextCharFormat m_borneFormat; /*!< \brief Format des bornes du code*/
    QTextCharFormat m_numeriqueFormat; /*!< \brief Format des valeurs numériques*/

    QColor couleur;

protected:
    void highlightBlock(const QString &text); //Déclaration en fonction protégé car c'est en protégé qu'elle est déclaré dans sa classe parente

public slots:
    void loadSettings();
};

#endif // COLORATION_H
