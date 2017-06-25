#ifndef TYALOGGEREXPORT_H
#define TYALOGGEREXPORT_H

#ifdef _WIN32
#  define TYA_DECL_EXPORT     __declspec(dllexport)
#  define TYA_DECL_IMPORT     __declspec(dllimport)
#else
#  define TYA_DECL_EXPORT
#  define TYA_DECL_IMPORT
#endif

#ifndef TYA_BUILD_LOGGER
#  define TYA_LOGGER_EXPORT TYA_DECL_EXPORT
#elif defined(TYA_USE_LOGGER) // use as dynamic linked library
#  define TYA_LOGGER_EXPORT TYA_DECL_IMPORT
#else // static link
#  define TYA_LOGGER_EXPORT
#endif

#endif // TYALOGGEREXPORT_H
