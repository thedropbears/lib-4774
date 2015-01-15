#include "ReadMpu.h"

ReadMpu::ReadMpu():Command("ReadMpu") {
    Requires(CommandBase::imu);
    SetInterruptible(false);
    SetRunWhenDisabled(true);
}

void ReadMpu::Initialize() {
    CommandBase::imu->UpdateValues();
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
