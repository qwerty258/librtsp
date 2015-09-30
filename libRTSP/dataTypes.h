#pragma once

#include <WinSock2.h>

typedef enum _RTSPMethod
{
    UNSPECIFIED = 0,
    OPTIONS,
    DESCRIBE,
    ANNOUNCE,
    SETUP,
    PLAY,
    PAUSE,
    TEARDOWN,
    GET_PARAMETER,
    SET_PARAMETER,
    REDIRECT,
    RECORD
}RTSPMethod;

typedef struct _RTSPRequest
{
    RTSPMethod method;
    unsigned int sequenceNumber;
    char* userAgent;
}RTSPRequest;

typedef struct _RTSPResponse
{
    unsigned int sequenceNumber;
    unsigned int statusCode;
}RTSPResponse;

typedef struct _RTSPClientInstance
{
    char* URI;
    RTSPProtocol protocol;
    SOCKET sock;
    RTSPRequest request;
    RTSPResponse response;
}RTSPClientInstance;