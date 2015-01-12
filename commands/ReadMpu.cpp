#include "ReadMpu.h"

ReadMpu::ReadMpu():Command("ReadMpu") {
    Requires(CommandBase::imu);
    SetInterruptible(false);
    SetRunWhenDisabled(true);
    CommandBase::imu->UpdateValues();
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
