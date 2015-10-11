#ifdef HIJACKLIB_EXPORTS
#define HIJACKLIB_API __declspec(dllexport)
#else
#define HIJACKLIB_API __declspec(dllimport)
#endif

HIJACKLIB_API void dummyfn();

int myhookfoo(int a);
