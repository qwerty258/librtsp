#include "libRTSP.h"
#include "dataTypes.h"
#include "handleError.h"
#include "RTSPURIParser.h"
#include <limits.h>

#ifdef _MSC_VER
#ifdef _DEBUG // for memory leak check
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif // _DEBUG
#endif // _MSC_VER

// Windows Header Files:
#include <SDKDDKVer.h>
#include <Windows.h>

LIBRTSP_API unsigned int initializeDLLAsRTSPClient(void)
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

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
        pRTSPClientInstance->request.userAgent = _strdup("libRTSP");
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
            if(0 != result)
            {
                handleErrorForLibRTSP("closesocket", __FILE__, __LINE__, WSAGetLastError());
            }
        }
        if(NULL != (*pRTSPClientInstance)->URI)
        {
            free((*pRTSPClientInstance)->URI);
        }
        if(NULL != (*pRTSPClientInstance)->request.userAgent)
        {
            free((*pRTSPClientInstance)->request.userAgent);
        }
        free(*pRTSPClientInstance);
        (*pRTSPClientInstance) = NULL;
    }
}

LIBRTSP_API unsigned int setRTSPURI(RTSPClientHandle handle, char* URI)
{
    RTSPClientInstance* pRTSPClientInstance = handle;
    unsigned int setResult = UINT_MAX;
    if(NULL != pRTSPClientInstance && NULL != URI)
    {
        if(NULL != pRTSPClientInstance->URI)
        {
            free(pRTSPClientInstance->URI);
        }
        pRTSPClientInstance->URI = _strdup(URI);
        // to do: implement IPv6
        pRTSPClientInstance->serverSockaddr.sin_family = AF_INET;
        setResult = parseRTSPURI(pRTSPClientInstance->URI, &pRTSPClientInstance->serverSockaddr.sin_addr.S_un.S_addr, &pRTSPClientInstance->serverSockaddr.sin_port);
    }
    return setResult;
}

LIBRTSP_API unsigned int setRTSPProtocol(RTSPClientHandle handle, RTSPProtocol protocol)
{
    RTSPClientInstance* pRTSPClientInstance = handle;
    unsigned int setResult = UINT_MAX;
    if(NULL != pRTSPClientInstance)
    {
        pRTSPClientInstance->protocol = protocol;
        if(RTSPUsingTCP == protocol)
        {
            pRTSPClientInstance->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if(INVALID_SOCKET == pRTSPClientInstance->sock)
            {
                handleErrorForLibRTSP("socket", __FILE__, __LINE__, WSAGetLastError());
            }
            setResult = 0;
        }
        else if(RTSPUsingUDP == protocol)
        {
            pRTSPClientInstance->sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if(INVALID_SOCKET == pRTSPClientInstance->sock)
            {
                handleErrorForLibRTSP("socket", __FILE__, __LINE__, WSAGetLastError());
            }
            setResult = 0;
        }
        else
        {
            setResult = UINT_MAX;
        }
    }
    return setResult;
}

LIBRTSP_API unsigned int setUserAgent(RTSPClientHandle handle, char* userAgent)
{
    RTSPClientInstance* pRTSPClientInstance = handle;
    unsigned int setResult = UINT_MAX;
    if(NULL != pRTSPClientInstance && NULL != userAgent)
    {
        if(NULL != pRTSPClientInstance->request.userAgent)
        {
            free(pRTSPClientInstance->request.userAgent);
        }
        pRTSPClientInstance->request.userAgent = _strdup(userAgent);
        if(NULL == pRTSPClientInstance->request.userAgent)
        {
            setResult = UINT_MAX;
        }
        else
        {
            setResult = 0;
        }
    }
    return setResult;
}

LIBRTSP_API unsigned int tryConnect(RTSPClientHandle handle)
{
    RTSPClientInstance* pRTSPClientInstance = handle;
    unsigned int tryConnectResult = UINT_MAX;
    if(RTSPUsingTCP == pRTSPClientInstance->protocol)
    {
        tryConnectResult = connect(pRTSPClientInstance->sock, (struct sockaddr*)&pRTSPClientInstance->serverSockaddr, sizeof(sockaddr_in));
        if(0 != tryConnectResult)
        {
            tryConnectResult = UINT_MAX;
            handleErrorForLibRTSP("connect", __FILE__, __LINE__, WSAGetLastError());
        }
        else
        {
            tryConnectResult = 0;
        }
    }
    else if(RTSPUsingUDP == pRTSPClientInstance->protocol)
    {
        tryConnectResult = 0;
    }
    else
    {
        tryConnectResult = UINT_MAX;
    }
    return tryConnectResult;
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
