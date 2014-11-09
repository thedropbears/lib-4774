#ifndef DROPBONEIMU
#define DROPBONEIMU

#include "UdpReceiver.h"

#define BONE_PARSEDLEN 13 // the length of the packets coming over udp

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
        virtual double PIDGet();
        void resetYaw();
    private:
        double offset;
        double parsed[BONE_PARSEDLEN];
        virtual int parsePacket(char* recv_buffer, int received_bytes);
};
#endif
