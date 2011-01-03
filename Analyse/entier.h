#ifndef ENTIER_H
#define ENTIER_H

#include "variable.h"

class Entier : public Variable {
public:
	Entier(const QString& pNom, const QString& pDescription);
	virtual QString toString() const;

private:
	long int	m_valeur;
};

#endif // ENTIER_H
