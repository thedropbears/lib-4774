#include "DropBoneImu.h"

#include <cstdlib>
#include <cmath>


DropBoneImu::DropBoneImu(int port): UdpReceiver(4774, name) {
    offset = 0;
    time(&last_beat);
}

DropBoneImu::~DropBoneImu() {
}

int DropBoneImu::parsePacket(char* recv_buffer, int received_bytes) {
    char* end = recv_buffer;
    double next;
    for(int i = 0; i < BONE_PARSEDLEN-1; i++){
        next=strtod(end,&end);
        if (end != NULL) {
			end++; // skip the comma
		}
        parsed[i] = next;
    }
    return 0;
}

int DropBoneImu::sendBeat() {
    int sent_bytes = sendto(sock, beat, sizeof beat, 0, beaglebone, sizeof *beaglebone);
    return sent_bytes;
}

void DropBoneImu::subReceivePacket() {
    if(difftime(time(NULL), last_beat) >= 1) {
        if(sendBeat() > -1) {
        } else {
            broadcastable = false;
        }
    }
}

void DropBoneImu::subSocketInit() {
    struct addrinfo hints, *res;
    
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    
    getaddrinfo(BEAGLEIP, BEAGLEBEATPORT, &hints, &res);
    
    beaglebone = res->ai_addr;
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

double DropBoneImu::getYawAngle() {
    double yaw_angle;
    yaw_angle = atan2(sin(parsed[0]-offset),cos(parsed[0]-offset));
    return yaw_angle;
}

double DropBoneImu::getYawRate() {
    return parsed[5];
}

double DropBoneImu::PIDGet() {
    return getYawAngle();
}

void DropBoneImu::resetYaw() {
    offset = parsed[0];
}
