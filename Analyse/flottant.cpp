#include "flottant.h"

Flottant::Flottant(const QString& pNom, const QString& pDescription) : Variable(pNom, pDescription) {
}

QString Flottant::toString() const {
	return QString::number(m_valeur);
}
