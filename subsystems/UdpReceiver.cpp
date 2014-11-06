#include "UdpReceiver.h"

UdpReceiver::UdpReceiver(int initPort, const char* name): Subsystem(name) {
    port = initPort;
    socketInit();
}

UdpReceiver::~UdpReceiver() {
    close(sock);
}

void UdpReceiver::receivePacket() {
    if(!broadcastable)
        socketInit();

    char recvBuffer[BUFFSIZE];
    int receivedBytes;
    if(broadcastable)
        receivedBytes = recvfrom(sock, recvBuffer, BUFFSIZE, 0, NULL, NULL);
    int parseFlag;
    if(receivedBytes != -1)
        parseFlag = parsePacket(recvBuffer, receivedBytes);
}

void UdpReceiver::socketInit() {
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock == -1) // we have failed ot open a socket
        broadcastable = false;
    broadcastable = true;
}

bool UdpReceiver::isBroadcastable() {
    return broadcastable;
}
