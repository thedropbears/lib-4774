#ifndef MPU6050_LIB4774_h
#define MPU6050_LIB4774_h

#include "WPILib.h"
#define __arm__
#define __PGMSPACE_H_
#define delay(p) Wait(p)
#include "mpu6050/MPU6050.h"

namespace lib4774 {
class MPU6050 : public SensorBase, public PIDSource, public ::MPU6050 {
    public:
	    MPU6050();
        MPU6050(uint8_t address);
        virtual double PIDGet();
    private:
        virtual void run();
};

} // end namespace
#endif
