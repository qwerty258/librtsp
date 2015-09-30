#include "libRTSP.h"
#include <limits.h>
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

LIBRTSP_API unsigned int initializeDLLAsRTSPClient(void)
{
    return 0;
}

LIBRTSP_API unsigned int freeRTSPClinetDLL(void)
{
    return 0;
}

LIBRTSP_API unsigned int initializeDLLAsRTSPServer(void)
{
    return 0;
}

LIBRTSP_API unsigned int freeRTSPServerDLL(void)
{
    return 0;
}
