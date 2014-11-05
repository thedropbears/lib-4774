#include "UdpReceiver.h"

#include <cassert>

UdpReceiver::UdpReceiver(int initPort): Subsystem("Beaglebone") {
    port = initPort;
    assert(socketInit());
}

UdpReceiver::~UdpReceiver() {
}

void UdpReceiver::receiveBroadcast() {
    recvfrom(sock, &lastBroadcast[0], lastBroadcast.size(), 0, NULL, NULL); 
}

bool UdpReceiver::socketInit() {
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock == -1) // we have failed ot open a socket
        return false
    return true
}
