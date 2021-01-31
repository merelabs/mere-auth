#ifndef MERE_AUTH_GLOBAL_H
#define MERE_AUTH_GLOBAL_H

#include <QtCore/QtGlobal>
#include <QDebug>

#if defined MERE_AUTH_LIB
#define MERE_AUTH_LIBSPEC Q_DECL_EXPORT
#else
#define MERE_AUTH_LIBSPEC Q_DECL_IMPORT
#endif

#endif // MERE_AUTH_GLOBAL_H
