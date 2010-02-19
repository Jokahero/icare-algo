#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtCore/QString>
#include <QtPlugin>
#include <QtGui/QDockWidget>
#include <QtGui/QMenu>

#include "../Analyse/analyse.h"
#include "../Analyse/expressionlogique.h"
#include "../Analyse/mathexp.h"

/*!
  \brief Définit l'interface utilisable par les plugins.
*/
class PluginInterface : public QObject {
public:
    virtual ~PluginInterface() {}
    virtual QString getNom() = 0;
    virtual QDockWidget* getDockWidget() { return 0; };
    virtual QMenu* getMenu() { return 0; };

public slots:
    virtual void variableAjoutee(QString /*pNomVar*/, QString /*pType*/, QString /*pDescription*/) {};
    virtual void variableModifiee(QString /*pNomVar*/, QString /*pValeur*/) {};
    virtual void reinitialisationGlossaire() {};
    virtual void lancerAnalyse(QFile* /*pFichier*/) {};
    virtual void lancerExecution() {};
    virtual void erreurLogique(ExpressionLogique::erreur /*pErreur*/) {};
    virtual void erreurMathematique(MathExp::erreur /*pErreur*/) {};
    virtual void erreurAnalyse(Analyse::erreur /*pErreur*/, int /*pNumLigne*/) {};
    virtual void afficher(QString /*pChaine*/) {};
    virtual void analyseSyntaxiqueTerminee(bool /*pOk*/) {};
    virtual void analyseSemantiqueTerminee(bool /*pOk*/) {};
};

Q_DECLARE_INTERFACE(PluginInterface,
                    "com.icare.Plugin.ModuleInterface/1.0");

#endif // PLUGININTERFACE_H
