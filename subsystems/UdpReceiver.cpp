#include "UdpReceiver.h"

#include <commands/ReceiveUdp.h>

UdpReceiver::UdpReceiver(int port, const char* name): Subsystem(name) {
    this->port = port;
    noPacketCount = 0;
    socketInit();
}

UdpReceiver::~UdpReceiver() {
    close(sock);
}

void UdpReceiver::receivePacket() {
    if(!broadcastable)
        socketInit();

    char recv_buffer[BUFFSIZE];
    int received_bytes = -1;
    if(broadcastable)
        received_bytes = recvfrom(sock, recv_buffer, BUFFSIZE, 0, NULL, NULL);
    int parse_flag;
    if(received_bytes != -1){
        parse_flag = parsePacket(recv_buffer, received_bytes);
        noPacketCount = 0;
    }
    else
        noPacketCount++;
}

void UdpReceiver::socketInit() {
    int bound, timeopt;
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in recvAddr;
    memset(&recvAddr,'\0', sizeof(recvAddr));
    recvAddr.sin_family = AF_INET;
    recvAddr.sin_port = htons(port);
    recvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 10000; //connection timeot
    timeopt = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
    bound = bind(sock, (struct sockaddr*) &recvAddr, sizeof recvAddr);

    if(sock == -1 || bound == -1 || timeopt == -1) // we have failed to create a socket
        broadcastable = false;
    else
        broadcastable = true;
}

bool UdpReceiver::isBroadcastable() {
    return broadcastable;
}

void UdpReceiver::InitDefaultCommand() {
    SetDefaultCommand(new ReceiveUdp(this));
}

bool UdpReceiver::timedOut() {
    if(noPacketCount>= PACKETTIMEOUT)
        return true;
    return false;
}
