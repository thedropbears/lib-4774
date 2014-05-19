#ifndef MPU6050_frc_h
#define MPU6050_frc_h

#include "WPILib.h"
#include "MPU6050.h"

class MPU6050_frc : public SensorBase, PIDSource, MPU6050 {
    public:
	    MPU6050_frc();
        virtual double PIDGet();

};

#endif
