
#ifndef GLOBJECTS_API_H
#define GLOBJECTS_API_H

#ifdef GLOBJECTS_STATIC_DEFINE
#  define GLOBJECTS_API
#  define GLOBJECTS_NO_EXPORT
#else
#  ifndef GLOBJECTS_API
#    ifdef globjects_EXPORTS
        /* We are building this library */
#      define GLOBJECTS_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define GLOBJECTS_API __declspec(dllimport)
#    endif
#  endif

#  ifndef GLOBJECTS_NO_EXPORT
#    define GLOBJECTS_NO_EXPORT 
#  endif
#endif

#ifndef GLOBJECTS_DEPRECATED
#  define GLOBJECTS_DEPRECATED __declspec(deprecated)
#endif

#ifndef GLOBJECTS_DEPRECATED_EXPORT
#  define GLOBJECTS_DEPRECATED_EXPORT GLOBJECTS_API GLOBJECTS_DEPRECATED
#endif

#ifndef GLOBJECTS_DEPRECATED_NO_EXPORT
#  define GLOBJECTS_DEPRECATED_NO_EXPORT GLOBJECTS_NO_EXPORT GLOBJECTS_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define GLOBJECTS_NO_DEPRECATED
#endif

#endif
