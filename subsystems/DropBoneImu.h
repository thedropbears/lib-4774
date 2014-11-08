#ifndef DROPBONEIMU
#define DROPBONEIMU

#include "UdpReceiver.h"

#define PORT 4774 //the default port if no other is specified

#define PARSEDLEN 13 // the length of the packets coming over udp

class DropBoneImu: public UdpReceiver, public PIDSource {
    public:
        DropBoneImu(int port=PORT);
        ~DropBoneImu();
        double* getEuler();
        double* getGyro();
        double* getAccel();
        double* getQuat();
        double getYawAngle();
        double getYawRate();
        virtual double PIDGet();
        void resetYaw();
    private:
        double offset;
        double parsed[PARSEDLEN];
        virtual int parsePacket(char* recv_buffer, int received_bytes);
};
#endif
