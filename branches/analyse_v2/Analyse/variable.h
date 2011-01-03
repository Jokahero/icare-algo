#ifndef VARIABLE_H
#define VARIABLE_H

#include <QtCore/QString>

class Variable {
public:
	Variable(const QString& pNom, const QString& pDescription);
	virtual QString toString() const = 0;

private:
	QString	m_nom;
	QString	m_description;
	bool	m_isInit;
};

#endif // VARIABLE_H
