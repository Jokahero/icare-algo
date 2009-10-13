#ifndef MATHEXP_GLOBAL_H
#define MATHEXP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MATHEXP_LIBRARY)
#  define MATHEXPSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MATHEXPSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MATHEXP_GLOBAL_H
