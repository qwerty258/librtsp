#ifdef LIBRTSP_EXPORTS
#define LIBRTSP_API __declspec(dllexport)
#else
#define LIBRTSP_API __declspec(dllimport)
#endif

LIBRTSP_API int fnlibRTSP(void);
