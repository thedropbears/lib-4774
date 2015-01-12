#ifndef READMPU
#define READMPU

#include <WPILib.h>

#include "../../CommandBase.h"

#include "../subsystems/Mpu6050.h"

class ReadMpu: public Command {
    public:
        ReadMpu();
        virtual void Initialize();
        virtual void Execute();
        virtual bool IsFinished();
        virtual void End();
        virtual void Interrupted();
    private:
};

#endif
