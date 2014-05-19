#ifndef MPU6050_frc_h
#define MPU6050_frc_h

#include "WPILib.h"
#include "MPU6050.h"

class MPU6050_frc : public SensorBase, public PIDSource, public MPU6050 {
    public:
	    MPU6050_frc();
        MPU6050_frc(uint8_t address);
        virtual double PIDGet();

};

#endif
