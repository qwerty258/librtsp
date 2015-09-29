#ifdef LIBRTSP_EXPORTS
#define LIBRTSP_API __declspec(dllexport)
#else
#define LIBRTSP_API __declspec(dllimport)
#endif

#ifdef __cplusplus
#define LIBRTSPEXTERNC_HEAD extern "C" {
#define LIBRTSPEXTERNC_TILE }
#endif // __cplusplus

LIBRTSPEXTERNC_HEAD

LIBRTSP_API int fnlibRTSP(void);

LIBRTSPEXTERNC_TILE