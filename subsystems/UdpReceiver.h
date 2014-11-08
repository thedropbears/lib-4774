#ifndef UDPRECEIVER
#define UDPRECEIVER

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <WPILib.h>

#define BUFFSIZE 1024

#define PACKETTIMEOUT 10

class UdpReceiver: public Subsystem {
    public:
        int port;
        UdpReceiver(int port, const char* name);
        ~UdpReceiver();
        bool isBroadcastable();
        void InitDefaultCommand();
        void receivePacket();
        bool timedOut(); // return the number of calls to receive packet since we last got one
    private:
        int sock, noPacketCount;
        bool broadcastable; // true if the socket is ready and we cajn broadcast
        void socketInit();
        virtual int parsePacket(char* recv_buffer, int received_bytes) = 0; // int is error code return
};
#endif
