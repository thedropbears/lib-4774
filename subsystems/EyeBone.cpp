#include "EyeBone.h"

EyeBone::EyeBone(): UdpReceiver(PORT, "EyeBone"){
}

EyeBone::~EyeBone() {
}

int EyeBone::parseBroadcast(char* recv_buffer, int received_bytes) {
    return 0;
}
