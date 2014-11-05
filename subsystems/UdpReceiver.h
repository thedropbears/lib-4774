#ifndef UDPRECEIVER
#define UDPRECEIVER

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>

#include <WPILib.h>

#define BUFFSIZE 1024

class UdpReceiver: public Subsystem {
    public:
        int port;
        UdpReceiver(int initPort);
        ~UdpReceiver();
        bool isBroadcastable();
    private:
        int sock;
        bool broadcastable; // true if the socket is ready and we cajn broadcast
        void receiveBroadcast();
        void socketInit();
        virtual int parseBroadcast(char* recvBuffer, int receivedBytes) = 0; // int is error code return
};
#endif
