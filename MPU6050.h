#ifndef MPU6050_LIB4774_h
#define MPU6050_LIB4774_h

#include "WPILib.h"
#include "mpu6050/helper_3dmath.h"

namespace lib4774 {
class MPU6050 : public SensorBase, public PIDSource {
    public:
	    MPU6050();
        double PIDGet();
        double getRotationX();
        double getRotationY();
        double getRotationZ();
        unsigned char dmpGetEuler(double *data);
        unsigned char dmpGetYawPitchRoll(double *data, Quaternion *q, VectorFloat *gravity);

    private:
        void run();
};

} // end namespace
#endif
