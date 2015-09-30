#include "libRTSP.h"
#include "dataTypes.h"
#include <limits.h>
// Windows Header Files:
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

LIBRTSP_API unsigned int initializeDLLAsRTSPClient(void)
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(0 != result)
    {
        return UINT_MAX;
    }
    return 0;
}

LIBRTSP_API unsigned int freeRTSPClinetDLL(void)
{
    int result = WSACleanup();
    if(0 != result)
    {
        return UINT_MAX;
    }
    return 0;
}

LIBRTSP_API RTSPClientHandle getNewRTSPHandle(void)
{
    RTSPClientInstance* pRTSPClientInstance = (RTSPClientInstance*)calloc(1, sizeof(RTSPClientInstance));
    return pRTSPClientInstance;
}

LIBRTSP_API void freeRTSPHandle(RTSPClientHandle* handle)
{
    if(NULL != handle || NULL != (*handle))
    {
        free(*handle);
        (*handle) = NULL;
    }
}

LIBRTSP_API unsigned int initializeDLLAsRTSPServer(void)
{
    unsigned int result = initializeDLLAsRTSPClient();
    return result;
}

LIBRTSP_API unsigned int freeRTSPServerDLL(void)
{
    unsigned int result = freeRTSPClinetDLL();
    return result;
}
