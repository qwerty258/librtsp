#include "libRTSP.h"
#include "handleError.h"
#include "dataTypes.h"
#include <limits.h>
// Windows Header Files:
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

#define strdup _strdup

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
    if(NULL != pRTSPClientInstance)
    {
        pRTSPClientInstance->sock = INVALID_SOCKET;
    }
    return pRTSPClientInstance;
}

LIBRTSP_API void freeRTSPHandle(RTSPClientHandle* handle)
{
    RTSPClientInstance** pRTSPClientInstance = (RTSPClientInstance**)handle;
    int result = 0;
    if(NULL != pRTSPClientInstance || NULL != (*pRTSPClientInstance))
    {
        if(INVALID_SOCKET != (*pRTSPClientInstance)->sock)
        {
            result = closesocket((*pRTSPClientInstance)->sock);
        }
        free(*pRTSPClientInstance);
        (*pRTSPClientInstance) = NULL;
    }
    if(0 != result)
    {
        handleErrorForLibRTSP("closesocket", __FILE__, __LINE__, WSAGetLastError());
    }
}

LIBRTSP_API void setRTSPURI(RTSPClientHandle handle, char* URI)
{
    RTSPClientInstance* pRTSPClientInstance = handle;
    if(NULL != pRTSPClientInstance)
    {

        if(NULL != pRTSPClientInstance->URI)
        {
            free(pRTSPClientInstance->URI);
        }
        pRTSPClientInstance->URI = strdup(URI);
    }
}

LIBRTSP_API void setRTSPProtocol(RTSPClientHandle handle, RTSPProtocol protocol)
{
    RTSPClientInstance* pRTSPClientInstance = handle;
    if(NULL != pRTSPClientInstance)
    {
        if(RTSPUsingTCP == protocol)
        {
            pRTSPClientInstance->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if(INVALID_SOCKET == pRTSPClientInstance->sock)
            {
                handleErrorForLibRTSP("socket", __FILE__, __LINE__, WSAGetLastError());
            }
        }
        else if(RTSPUsingUDP == protocol)
        {
            pRTSPClientInstance->sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if(INVALID_SOCKET == pRTSPClientInstance->sock)
            {
                handleErrorForLibRTSP("socket", __FILE__, __LINE__, WSAGetLastError());
            }
        }
        else
        {
            handleErrorForLibRTSP("setRTSPProtocol unknow protocol", __FILE__, __LINE__, 0);
        }
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
