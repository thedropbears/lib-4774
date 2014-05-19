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

MPU6050_frc :: MPU6050_frc(uint8_t address) : MPU6050(address){
    MPU6050_frc();
}

double MPU6050_frc :: PIDGet() {
    return getRotationZ();
}
