#include <libRTSP.h>

int main(int argc, char* argv[])
{
    unsigned int result = initializeDLLAsRTSPClient();

    RTSPClientHandle handle = getNewRTSPHandle();

    setRTSPURI(handle, "rtsp://192.168.10.222:554/Streaming/Channels/1?transportmode=unicast");

    setRTSPProtocol(handle, RTSPUsingTCP);

    freeRTSPHandle(&handle);

    result = freeRTSPClinetDLL();
    return 0;
}

