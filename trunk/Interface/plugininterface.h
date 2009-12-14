#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtCore/QString>
#include <QtPlugin>
#include <QtGui/QDockWidget>
#include "../ExpressionsMathematiques/mathexp.h"
#include "../Analyse/analyse.h"

/*!
  \brief Définit l'interface utilisable par les plugins.
*/
class PluginInterface : public QObject{
public:
    virtual ~PluginInterface() {}
    virtual QString getNom() = 0;
    virtual QDockWidget* getDockWidget() { return NULL; };

public slots:
    void variableAjoutee(QString /*pNomVar*/, QString /*pType*/, QString /*pDescription*/) {};
    void variableModifiee(QString /*pNomVar*/, QString /*pValeur*/) {};
    void reinitialisationGlossaire();
    void lancerAnalyse(QFile* /*pFichier*/);
    void erreurMathematique(MathExp::erreur /*pErreur*/);
    void erreurAnalyse(Analyse::erreur /*pErreur*/);
};

Q_DECLARE_INTERFACE(PluginInterface,
                    "com.icare.Plugin.ModuleInterface/1.0");

#endif // PLUGININTERFACE_H
