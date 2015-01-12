#include "ReadMpu.h"

ReadMpu::ReadMpu(Mpu6050* imu):Command("ReadMpu") {
    this->imu = imu;
    Requires(imu);
    SetInterruptible(false);
    SetRunWhenDisabled(true);
    imu->UpdateValues();
}

void ReadMpu::Initialize() {
}

void ReadMpu::Execute() {
}

bool ReadMpu::IsFinished() {
    return true;
}

void ReadMpu::End() {
}

void ReadMpu::Interrupted() {
    End();
}
