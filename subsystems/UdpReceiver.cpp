#include "UdpReceiver.h"

#include <commands/ReceiveUdp.h>

static char beat[] = "1";

UdpReceiver::UdpReceiver(int port, const char name[], const char* beat_dest): Subsystem(name) {
    this->port = port;
    this->beat_dest = beat_dest;
    noPacketCount = 0;
    socketInit();
    if(beat_dest[0] == '0' && beat_dest[1] != '.') {
        beating = false;
    } else {
        beating = true;
        time(&last_beat);
    }
}

UdpReceiver::~UdpReceiver() {
    close(sock);
}

void UdpReceiver::receivePacket() {
    if(!receiving)
        socketInit();

    if(beating && difftime(time(NULL), last_beat) >= 1) {
        if(sendBeat() > -1) {
        } else {
            receiving = false;
        }
    }

    char recv_buffer[BUFFSIZE];
    int received_bytes = -1;
    if(receiving)
        received_bytes = recvfrom(sock, recv_buffer, BUFFSIZE, 0, NULL, NULL);
    int parse_flag;
    if(received_bytes != -1){
        parse_flag = parsePacket(recv_buffer, received_bytes);
        noPacketCount = 0;
    }
    else
        noPacketCount++;
}

void UdpReceiver::socketInit() {
    int bound, timeopt;
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in recvAddr;
    memset(&recvAddr,'\0', sizeof(recvAddr));
    recvAddr.sin_family = AF_INET;
    recvAddr.sin_port = htons(port);
    recvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(beating) {
        struct addrinfo hints, *res;
    
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;
        
        sprintf(port_string, "%d", port);
    
        getaddrinfo(beat_dest, port_string, &hints, &res);
    
        beat_addr = res->ai_addr;
    }

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 10000; //connection timeot
    timeopt = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
    bound = bind(sock, (struct sockaddr*) &recvAddr, sizeof recvAddr);

    if(sock == -1 || bound == -1 || timeopt == -1) // we have failed to create a socket
        receiving = false;
    else
        receiving = true;
}

int UdpReceiver::sendBeat() {
    int sent_bytes = sendto(sock, beat, sizeof beat, 0, beat_addr, sizeof *beat_addr);
    return sent_bytes;
}

bool UdpReceiver::isReceiving() {
    return receiving;
}

void UdpReceiver::InitDefaultCommand() {
    SetDefaultCommand(new ReceiveUdp(this));
}

bool UdpReceiver::timedOut() {
    if(noPacketCount>= PACKETTIMEOUT)
        return true;
    return false;
}
