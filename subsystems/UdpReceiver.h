#ifndef UDPRECEIVER
#define UDPRECEIVER

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

#include <WPILib.h>

#define BUFFSIZE 1024

#define PACKETTIMEOUT 10

class UdpReceiver: public Subsystem {
    public:
        int port;
        UdpReceiver(int port, const char name[], const char* beat_dest="0");
        ~UdpReceiver();
        bool isReceiving();
        void InitDefaultCommand();
        void receivePacket();
        bool timedOut(); // return the number of calls to receive packet since we last got one
    private:
        time_t last_beat;
        struct sockaddr* beat_addr; //the address of the device we are sending heartbeats to
        int noPacketCount, sock;
        bool receiving; // true if the socket is ready and we can broadcast
        bool beating = true; //true if we are sending heartbeats
        const char* beat_dest;
        char* port_string;
        void socketInit();
        virtual int parsePacket(char* recv_buffer, int received_bytes) = 0; // int is error code return
        int sendBeat();
};
#endif
