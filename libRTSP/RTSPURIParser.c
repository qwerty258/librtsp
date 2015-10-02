#include "RTSPURIParser.h"
#include <WS2tcpip.h>
#include <WinSock2.h>

unsigned int parseRTSPURI(char* URI, unsigned long* IPv4, unsigned short* port)
{
    char* URITemp = _strdup(URI);
    char* currnetPosition;
    char* tempPosition;
    char* end;
    char IPString[21];
    int result;
    unsigned int parseResult = UINT_MAX;
    if(NULL != URITemp)
    {
        memset(IPString, 0x0, 21);
        *port = htons(554);
        if(0 == strncmp("rtsp://", URITemp, strnlen("rtsp://", 20)));
        {
            currnetPosition = URITemp + strnlen("rtsp://", 20);
            tempPosition = strstr(currnetPosition, ":");
            if(NULL != tempPosition)
            {
                *port = htons((unsigned short)strtoul(tempPosition + 1, &end, 10));
            }
            memcpy_s(IPString, 20, currnetPosition, tempPosition - currnetPosition);
            result = inet_pton(AF_INET, (char*)IPString, IPv4);
            if(1 != result)
            {
                parseResult = UINT_MAX;
            }
            else
            {
                parseResult = 0;
            }
        }
        free(URITemp);
    }
    return parseResult;
}