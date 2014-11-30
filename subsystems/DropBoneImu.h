#ifndef DROPBONEIMU
#define DROPBONEIMU

#include "UdpReceiver.h"
#include <time.h>

#define BONE_PARSEDLEN 13 // the length of the packets coming over udp

#define BEAGLEIP "192.168.7.2"
#define BEAGLEBEATPORT "4773" //needs to be a string

class DropBoneImu: public UdpReceiver, public PIDSource {
    public:
        DropBoneImu(int port=4774);
        ~DropBoneImu();
        double* getEuler();
        double* getGyro();
        double* getAccel();
        double* getQuat();
        double getYawAngle();
        double getYawRate();
        double PIDGet();
        void resetYaw();
    private:
        time_t last_beat;
        struct sockaddr* beaglebone;
        char beat[2] = "1";
        double offset;
        double parsed[BONE_PARSEDLEN];
        virtual int parsePacket(char* recv_buffer, int received_bytes);
        int sendBeat();
        void subReceivePacket();
        void subSocketInit();
        const char* name = "DropBoneImu";
};
#endif
