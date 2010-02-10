#ifndef GESTIONNAIREPARAMETRES_H
#define GESTIONNAIREPARAMETRES_H

#include <QtCore/QObject>

class QByteArray;
class QColor;
class QSettings;

class GestionnaireParametres : public QObject {
public:
    static GestionnaireParametres* getInstance();
    void destroy();

    bool getNumerotationLignes();
    void setNumerotationLignes(bool pNum);

    bool getRetourLigne();
    void setRetourLigne(bool pRet);

    int getTailleTab();
    void setTailleTab(int pTaille);
    
    QColor getCouleurLigneActuelle();
    void setCouleurLigneActuelle(QColor pCol);

    QColor getCouleurCommentaires();
    void setCouleurCommentaires(QColor pCol);

    QColor getCouleurTypes();
    void setCouleurTypes(QColor pCol);

    QColor getCouleurNombres();
    void setCouleurNombres(QColor pCol);

    QColor getCouleurStructures();
    void setCouleurStructures(QColor pCol);

    QColor getCouleurBornes();
    void setCouleurBornes(QColor pCol);

    bool getPluginActif(QString pNom);
    void setPluginActif(QString pNom, bool pActif = true);

    bool getFenetreMax();
    void setFenetreMax(bool pMax);

    QByteArray getFenetreGeo();
    void setFenetreGeo(QByteArray pGeo);

private:
    static GestionnaireParametres *_instance;                      /*!< \brief Seule instance de la classe (Singleton). */
    GestionnaireParametres();
    ~GestionnaireParametres();

    QSettings* m_set;
};

#endif // GESTIONNAIREPARAMETRES_H
