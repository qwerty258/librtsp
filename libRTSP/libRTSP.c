#include "libRTSP.h"
#include <limits.h>
// Windows Header Files:
#include <SDKDDKVer.h>
#include <WinSock2.h>
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
