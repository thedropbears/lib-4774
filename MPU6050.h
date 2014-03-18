#ifndef MPU6050_h
#define MPU6050_h

#include "WPILib.h"

class MPU6050 : public SensorBase, PIDSource {
    public:
        double PIDGet();
        
        enum Axes {kAxis_X=0x00, kAxis_Y=0x02, kAxis_Z=0x04};
	    struct AllAxes
	    {
		    double XAxis;
		    double YAxis;
		    double ZAxis;
	    };
        
        float GetAngle();
        void Reset();
        
        double GetAcceleration(Axes axis);
        AllAxes GetAccelerations();
    private:
        void InitGyro();
    protected:
        I2C* m_i2c;
	
};

#endif
