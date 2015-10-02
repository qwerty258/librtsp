#include <libRTSP.h>

int main(int argc, char* argv[])
{
    unsigned int result = initializeDLLAsRTSPClient();

    RTSPClientHandle handle = getNewRTSPHandle();

    result = setRTSPURI(handle, "rtsp://192.168.10.222:554/Streaming/Channels/1?transportmode=unicast");

    result = setRTSPProtocol(handle, RTSPUsingTCP);

    result = setUserAgent(handle, "test UserAgent");

    freeRTSPHandle(&handle);

    result = freeRTSPClinetDLL();
    return 0;
}

