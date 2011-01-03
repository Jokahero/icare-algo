#ifndef BOOLEEN_H
#define BOOLEEN_H

#include "variable.h"

class Booleen : public Variable {
public:
	Booleen(const QString& pNom, const QString& pDescription);
	virtual QString toString() const;

private:
	bool	m_valeur;
};

#endif // BOOLEEN_H
