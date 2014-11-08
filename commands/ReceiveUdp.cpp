#include "ReceiveUdp.h"

ReceiveUdp::ReceiveUdp(UdpReceiver* receiver):Command("ReceiveUdp") {
    this->receiver = receiver;
    Requires(receiver);
    SetInterruptible(false);
    SetRunWhenDisabled(true);
}

void ReceiveUdp::Initialize() {
}

void ReceiveUdp::Execute() {
    receiver->receivePacket();
}

bool ReceiveUdp::IsFinished() {
    return false;
}

void ReceiveUdp::End() {
}

void ReceiveUdp::Interrupted() {
    End();
}
