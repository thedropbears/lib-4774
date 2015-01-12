#include "ReceiveUdp.h"

ReadMpu::ReadMpu(Mpu6050* imu):Command("ReadMpu") {
    this->imu = imu;
    Requires(imu);
    SetInterruptible(false);
    SetRunWhenDisabled(true);
}

void ReceiveUdp::Initialize() {
}

void ReceiveUdp::Execute() {
    imu->ReadInterrupt();
}

bool ReceiveUdp::IsFinished() {
    return false;
}

void ReceiveUdp::End() {
}

void ReceiveUdp::Interrupted() {
    End();
}
