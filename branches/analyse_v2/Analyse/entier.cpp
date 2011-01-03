#include "entier.h"

Entier::Entier(const QString& pNom, const QString& pDescription) : Variable(pNom, pDescription) {
}

QString Entier::toString() const {
	return QString::number(m_valeur);
}
