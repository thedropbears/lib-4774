#include "MPU6050.h"

lib4774::MPU6050::MPU6050(){
	initialize();
    //dmpInitialize();
    setXGyroOffset(220);
    setYGyroOffset(76);
    setZGyroOffset(-85);
    setZAccelOffset(1788);
    //setDMPEnabled(true);
    
}

lib4774::MPU6050::MPU6050(uint8_t address) : MPU6050(address){
    MPU6050();
}

double lib4774::MPU6050::PIDGet() {
    return getRotationZ();
}
