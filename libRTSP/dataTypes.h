#pragma once

typedef enum _RTSPMethod
{
    OPTIONS = 1,
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
    unsigned int statusCode
}RTSPResponse;