#include "UdpReceiver.h"

UdpReceiver::UdpReceiver(int port, const char* name): Subsystem(name) {
    this->port = port;
    socketInit();
}

UdpReceiver::~UdpReceiver() {
    close(sock);
}

void UdpReceiver::receivePacket() {
    if(!broadcastable)
        socketInit();

    char recv_buffer[BUFFSIZE];
    int received_bytes;
    if(broadcastable)
        received_bytes = recvfrom(sock, recv_buffer, BUFFSIZE, 0, NULL, NULL);
    int parse_flag;
    if(received_bytes != -1)
        parse_flag = parsePacket(recv_buffer, received_bytes);
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
