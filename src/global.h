#ifndef MERE_AUTH_GLOBAL_H
#define MERE_AUTH_GLOBAL_H

#include <QtCore/QtGlobal>

#include <iostream>
#include <string>

#if defined MERE_AUTH_LIB
#define MERE_AUTH_LIB_SPEC Q_DECL_EXPORT
#else
#define MERE_AUTH_LIB_SPEC Q_DECL_IMPORT
#endif

#endif // MERE_AUTH_GLOBAL_H
