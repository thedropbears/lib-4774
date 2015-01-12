#ifndef READMPU
#define READMPU

#include <WPILib.h>

#include "../subsystems/Mpu6050.h"

class ReadMpu: public Command {
    public:
        ReadMpu(Mpu6050* imu);
        virtual void Initialize();
        virtual void Execute();
        virtual bool IsFinished();
        virtual void End();
        virtual void Interrupted();
    private:
        Mpu6050*  imu;
};

#endif
