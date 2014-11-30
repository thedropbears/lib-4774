#ifndef UDPRECEIVER
#define UDPRECEIVER

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <WPILib.h>

#define BUFFSIZE 1024

#define PACKETTIMEOUT 10

class UdpReceiver: public Subsystem {
    public:
        int port;
        UdpReceiver(int port, const char name[]);
        ~UdpReceiver();
        bool isBroadcastable();
        void InitDefaultCommand();
        void receivePacket();
        bool timedOut(); // return the number of calls to receive packet since we last got one
    private:
        int noPacketCount;
        void socketInit();
        virtual int parsePacket(char* recv_buffer, int received_bytes) = 0; // int is error code return
        //these allow subclasses to add functionality to pre written methods; these are called from within the UdpReceiver method
    protected:
        int sock;
        bool broadcastable; // true if the socket is ready and we can broadcast
        virtual void subReceivePacket() = 0;
        virtual void subSocketInit() = 0;
};
#endif
