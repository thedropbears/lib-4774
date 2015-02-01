#include "ReadMpu.h"

ReadMpu::ReadMpu(Mpu6050 *imu):Command("ReadMpu") {
    Requires(imu);
    SetInterruptible(false);
    SetRunWhenDisabled(true);
    this->imu = imu;
}

void ReadMpu::Initialize() {

    imu->UpdateValues();
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
