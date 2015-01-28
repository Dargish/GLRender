#if defined _WIN32
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined __GNUC__
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#else
#warning "Unrecognised Operating System"
#define EXPORT
#define IMPORT
#endif

#if defined GLRENDER_EXPORT
#define GLRENDERAPI EXPORT
#else
#define GLRENDERAPI IMPORT
#endif