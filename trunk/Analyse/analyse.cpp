#include "analyse.h"
#include "analysesyntaxique.h"
#include "analysesemantique.h"

Analyse::Analyse() {
}

Glossaire* Analyse::getGlossaire() {
    return m_glossaire;
}
