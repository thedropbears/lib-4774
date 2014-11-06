#include "EyeBone.h"

EyeBone::EyeBone(): UdpReceiver(PORT, "EyeBone"){
}

EyeBone::~EyeBone() {
}

int EyeBone::parseBroadcast(char* recvBuffer, int receivedBytes) {
    return 0;
}
