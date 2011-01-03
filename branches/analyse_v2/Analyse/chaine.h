#ifndef CHAINE_H
#define CHAINE_H

#include "variable.h"

class Chaine : public Variable {
public:
	Chaine(const QString& pNom, const QString& pDescription);
	virtual QString toString() const;

private:
	QString	m_valeur;
};

#endif // CHAINE_H
