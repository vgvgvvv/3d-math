
#ifndef _3d_math_API_H
#define _3d_math_API_H

#ifdef _3d_math_BUILT_AS_STATIC
#  define _3d_math_API
#  define _3D_MATH_NO_EXPORT
#else
#  ifndef _3d_math_API
#    ifdef _3d_math_EXPORTS
        /* We are building this library */
#      define _3d_math_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define _3d_math_API __declspec(dllimport)
#    endif
#  endif

#  ifndef _3D_MATH_NO_EXPORT
#    define _3D_MATH_NO_EXPORT 
#  endif
#endif

#ifndef _3D_MATH_DEPRECATED
#  define _3D_MATH_DEPRECATED __declspec(deprecated)
#endif

#ifndef _3D_MATH_DEPRECATED_EXPORT
#  define _3D_MATH_DEPRECATED_EXPORT _3d_math_API _3D_MATH_DEPRECATED
#endif

#ifndef _3D_MATH_DEPRECATED_NO_EXPORT
#  define _3D_MATH_DEPRECATED_NO_EXPORT _3D_MATH_NO_EXPORT _3D_MATH_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef _3D_MATH_NO_DEPRECATED
#    define _3D_MATH_NO_DEPRECATED
#  endif
#endif

#endif /* _3d_math_API_H */
