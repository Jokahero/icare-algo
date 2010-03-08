#ifndef GESTIONNAIREPARAMETRES_H
#define GESTIONNAIREPARAMETRES_H

#include <QtCore/QObject>

class QByteArray;
class QColor;
class QSettings;
class QStringList;


/*! \brief Classe permettant de sauvegarder les préférences.

  Singleton.
  Définit la valeur par défaut de toutes les options.
*/
class GestionnaireParametres : public QObject {
public:
    static GestionnaireParametres* getInstance();
    void destroy();

    bool getNumerotationLignes() const;
    void setNumerotationLignes(bool pNum);

    bool getRetourLigne() const;
    void setRetourLigne(bool pRet);

    int getTailleTab() const;
    void setTailleTab(int pTaille);
    
    QColor getCouleurLigneActuelle() const;
    void setCouleurLigneActuelle(const QColor& pCol);

    QColor getCouleurCommentaires() const;
    void setCouleurCommentaires(const QColor& pCol);

    QColor getCouleurChaines() const;
    void setCouleurChaines(const QColor& pCol);

    QColor getCouleurTypes() const;
    void setCouleurTypes(const QColor& pCol);

    QColor getCouleurNombres() const;
    void setCouleurNombres(const QColor& pCol);

    QColor getCouleurStructures() const;
    void setCouleurStructures(const QColor& pCol);

    QColor getCouleurBornes() const;
    void setCouleurBornes(const QColor& pCol);

    bool getPluginActif(const QString& pNom) const;
    void setPluginActif(const QString& pNom, bool pActif = true);

    bool getFenetreMax() const;
    void setFenetreMax(bool pMax);

    QByteArray getFenetreGeo() const;
    void setFenetreGeo(const QByteArray& pGeo);

    QStringList getListeFichiersRecents() const;
    void setListeFichiersRecents(const QStringList& pListe);

private:
    static GestionnaireParametres *_instance;                      /*!< \brief Seule instance de la classe (Singleton). */
    GestionnaireParametres();
    ~GestionnaireParametres();

    QSettings* m_set;
};

#endif // GESTIONNAIREPARAMETRES_H
