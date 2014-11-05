#ifndef UDPRECEIVER
#define UDPRECEIVER

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>

#include <WPILib.h>

class UdpReceiver: public Subsystem {
    public:
        int port;
        UdpReceiver(int initPort);
        ~UdpReceiver();
    private:
        int sock;
        string lastBroadcast;
        void receiveBroadcast();
        bool socketInit();
        virtual int parseBroadcast() = 0; // int is error code return
};
#endif
