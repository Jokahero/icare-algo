#include "variable.h"

Variable::Variable(const QString& pNom, const QString& pDescription) : m_nom(pNom), m_description(pDescription) {
	m_isInit = false;
}
