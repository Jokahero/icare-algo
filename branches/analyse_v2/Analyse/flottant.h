#ifndef FLOTTANT_H
#define FLOTTANT_H

#include "variable.h"

class Flottant : public Variable {
public:
	Flottant(const QString& pNom, const QString& pDescription);
	virtual QString toString() const;

private:
	float	m_valeur;
};

#endif // FLOTTANT_H
