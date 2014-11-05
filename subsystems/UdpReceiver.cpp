#include "UdpReceiver.h"

UdpReceiver::UdpReceiver(int initPort): Subsystem("UdpReceiver") {
    port = initPort;
    socketInit();
}

UdpReceiver::~UdpReceiver() {
    close(sock);
}

void UdpReceiver::receiveBroadcast() {
    if(!broadcastable)
        socketInit();

    char recvBuffer[BUFFSIZE];
    int receivedBytes;
    if(broadcastable)
        receivedBytes = recvfrom(sock, recvBuffer, BUFFSIZE, 0, NULL, NULL);
    int parseFlag;
    if(receivedBytes != -1)
        parseFlag = parseBroadcast(recvBuffer, receivedBytes);
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
