#ifndef MPU6050_LIB4774_h
#define MPU6050_LIB4774_h

#include "WPILib.h"
#include "mpu6050/MPU6050.h"

namespace lib4774 {
class MPU6050 : public SensorBase, public PIDSource, public ::MPU6050 {
    public:
	    MPU6050();
        MPU6050(uint8_t address);
        double PIDGet();
    private:
        void run();
};

} // end namespace
#endif
