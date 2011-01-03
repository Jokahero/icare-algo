#include "chaine.h"

Chaine::Chaine(const QString& pNom, const QString& pDescription) : Variable(pNom, pDescription) {
}

QString Chaine::toString() const {
	return m_valeur;
}
