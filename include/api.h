#pragma once

#if defined _WIN32 || defined __CYGWIN__
#  define KaleidoRLQPController_DLLIMPORT __declspec(dllimport)
#  define KaleidoRLQPController_DLLEXPORT __declspec(dllexport)
#  define KaleidoRLQPController_DLLLOCAL
#else
// On Linux, for GCC >= 4, tag symbols using GCC extension.
#  if __GNUC__ >= 4
#    define KaleidoRLQPController_DLLIMPORT __attribute__((visibility("default")))
#    define KaleidoRLQPController_DLLEXPORT __attribute__((visibility("default")))
#    define KaleidoRLQPController_DLLLOCAL __attribute__((visibility("hidden")))
#  else
// Otherwise (GCC < 4 or another compiler is used), export everything.
#    define KaleidoRLQPController_DLLIMPORT
#    define KaleidoRLQPController_DLLEXPORT
#    define KaleidoRLQPController_DLLLOCAL
#  endif // __GNUC__ >= 4
#endif // defined _WIN32 || defined __CYGWIN__

#ifdef KaleidoRLQPController_STATIC
// If one is using the library statically, get rid of
// extra information.
#  define KaleidoRLQPController_DLLAPI
#  define KaleidoRLQPController_LOCAL
#else
// Depending on whether one is building or using the
// library define DLLAPI to import or export.
#  ifdef KaleidoRLQPController_EXPORTS
#    define KaleidoRLQPController_DLLAPI KaleidoRLQPController_DLLEXPORT
#  else
#    define KaleidoRLQPController_DLLAPI KaleidoRLQPController_DLLIMPORT
#  endif // KaleidoRLQPController_EXPORTS
#  define KaleidoRLQPController_LOCAL KaleidoRLQPController_DLLLOCAL
#endif // KaleidoRLQPController_STATIC
