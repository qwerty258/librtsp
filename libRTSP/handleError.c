#include "handleError.h"
#include <stdio.h>
#include <Windows.h>
void handleErrorForLibRTSP(char* message, char* sourceFile, int line, int errorCode)
{
    char errorMessage[2048];
    int result = sprintf_s(errorMessage, "message: %s\r\nfile: %s\r\nline: %d\r\nerror code: %d", message, sourceFile, line, errorCode);
    if(-1 == result)
    {
        return;
    }
    MessageBoxA(NULL, errorMessage, "ERROR", MB_OK);
}