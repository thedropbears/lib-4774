#include "MPU6050-frc.h"

MPU6050_frc :: MPU6050_frc(){
	initialize();
    //dmpInitialize();
    setXGyroOffset(220);
    setYGyroOffset(76);
    setZGyroOffset(-85);
    setZAccelOffset(1788);
    //setDMPEnabled(true);
    
}

double MPU6050_frc :: PIDGet() {
    return getRotationZ();
}
