#include "booleen.h"

Booleen::Booleen(const QString& pNom, const QString& pDescription) : Variable(pNom, pDescription) {
}

QString Booleen::toString() const {
	return m_valeur ? QString("vrai") : QString("faux");
}
