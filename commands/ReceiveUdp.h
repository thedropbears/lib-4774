#ifndef RECEIVEUDP
#define RECEIVEUDP

#include <WPILib.h>

#include "../subsystems/UdpReceiver.h"

class ReceiveUdp: public Command {
    public:
        ReceiveUdp(UdpReceiver* receiver);
        virtual void Initialize();
        virtual void Execute();
        virtual bool IsFinished();
        virtual void End();
        virtual void Interrupted();
    private:
        UdpReceiver*  receiver;
};

#endif
