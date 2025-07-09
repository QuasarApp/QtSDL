//#
//# Copyright (C) 2018-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef QtSDL_GLOBAL_H
#define QtSDL_GLOBAL_H

#include <QtCore/qglobal.h>

#define QTSDL_VERSION "0.90.8fef03d"

#if defined(QTSDL_LIBRARY)
#  define QTSDL_EXPORT Q_DECL_EXPORT
#else
#  define QTSDL_EXPORT Q_DECL_IMPORT
#endif

#endif //QtSDL_GLOBAL_H

