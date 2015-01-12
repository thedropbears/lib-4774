#include "ReadMpu.h"

ReadMpu::ReadMpu(Mpu6050* imu):Command("ReadMpu") {
    this->imu = imu;
    Requires(imu);
    SetInterruptible(false);
    SetRunWhenDisabled(true);
    imu->UpdateValues();
}

void ReceiveUdp::Initialize() {
}

void ReceiveUdp::Execute() {
}

bool ReceiveUdp::IsFinished() {
    return true;
}

void ReceiveUdp::End() {
}

void ReceiveUdp::Interrupted() {
    End();
}
