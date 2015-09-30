#ifdef LIBRTSP_EXPORTS
#define LIBRTSP_API __declspec(dllexport)
#else
#define LIBRTSP_API __declspec(dllimport)
#endif

#ifdef __cplusplus
#define LIBRTSPEXTERNC_HEAD extern "C" {
#define LIBRTSPEXTERNC_TILE }
#else
#define LIBRTSPEXTERNC_HEAD
#define LIBRTSPEXTERNC_TILE
#endif // __cplusplus

LIBRTSPEXTERNC_HEAD

// API for client usage begin

LIBRTSP_API unsigned int initializeDLLAsRTSPClient(void);

LIBRTSP_API unsigned int freeRTSPClinetDLL(void);

// API for client usage end

// API for server usage begin

LIBRTSP_API unsigned int initializeDLLAsRTSPServer(void);

LIBRTSP_API unsigned int freeRTSPServerDLL(void);

// API for serverusage end

LIBRTSPEXTERNC_TILE