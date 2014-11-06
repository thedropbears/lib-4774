#ifndef EYEBONE
#define EYEBONE

#include "UdpReceiver.h"

#define PORT 4775

class EyeBone: public UdpReceiver {
    public:
        EyeBone();
        ~EyeBone();
        double getTargetX();
        double getTargetY();
        double getTargetWidth();
        double getTargetHeight();
        double getTargetAngle();
    private:
        double parsed[5];
        virtual int parseBroadcast(char* recvBuffer, int receivedBytes);
};

#endif
