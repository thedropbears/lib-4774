#include "DropBoneImu.h"

#include <cstdlib>

DropBoneImu::DropBoneImu(int port): UdpReceiver(port, "DropBoneImu") {
}

DropBoneImu::~DropBoneImu() {
}

int DropBoneImu::parsePacket(char* recv_buffer, int received_bytes) {
    char* end = recv_buffer;
    double next;
    for(int i = 0; i < PARSEDLEN; i++){
        next=strtod(end+1,&end);
        parsed[i] = next;
    }
    return 0;
}

double* DropBoneImu::getEuler() {
    return parsed;
}

double* DropBoneImu::getGyro() {
    return parsed+3;
}

double* DropBoneImu::getAccel() {
    return parsed+6;
}

double* DropBoneImu::getQuat() {
    return parsed+9;
}
