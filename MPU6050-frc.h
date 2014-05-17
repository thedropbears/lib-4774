#ifndef MPU6050-frc_h
#define MPU6050-frc_h

#include "WPILib.h"


class MPU6050 : public SensorBase, PIDSource {
    public:
        virtual double PIDGet();
        
        enum Axes {kAxis_X=0x00, kAxis_Y=0x02, kAxis_Z=0x04};
        struct AllAxes{
            double XAxis;
            double YAxis;
            double ZAxis;
        };
        
        virtual double GetAngle(Axes axis);
        virtual double GetRate(Axes axis);
        virtual void Reset();
        
        virtual double GetAcceleration(Axes axis);
        virtual AllAxes GetAccelerations();
    private:
        virtual void InitGyro();
        virtual void InitImu();
    protected:
        I2C* m_i2c;
        static const uint8_t kAddress = 0x69;
        static const uint8_t kPowerCtlRegister = 0x2D;
        static const uint8_t kDataFormatRegister = 0x31;
        static const uint8_t kDataRegister = 0x32;
        static constexpr double kGsPerLSB = 0.00390625;
};

#endif
