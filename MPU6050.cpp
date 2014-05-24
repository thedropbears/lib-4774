#define __arm__
#define __PGMSPACE_H_
#define delay(p) Wait(p)
#include "mpu6050/MPU6050_6Axis_MotionApps20.h"
#include "MPU6050.h"

lib4774::MPU6050::MPU6050(){
	// We have to left shift the address by one because the WPI I2C
	// library doesn't do it for us.
	// It includes the R/W bit - so we need to account for it.
	// I2C addresses are 7 bits, but WPILib assumes we have the full 8.
	::MPU6050(MPU6050_DEFAULT_ADDRESS << 1);
    run();
}

lib4774::MPU6050::MPU6050(uint8_t address){
	// We have to left shift the address by one because the WPI I2C
	// library doesn't do it for us.
	// It includes the R/W bit - so we need to account for it.
	// I2C addresses are 7 bits, but WPILib assumes we have the full 8.
    ::MPU6050(address << 1);
    run();
}

void lib4774::MPU6050::run() {
    initialize();
    //dmpInitialize();
    setXGyroOffset(220);
    setYGyroOffset(76);
    setZGyroOffset(-85);
    setZAccelOffset(1788);
    //setDMPEnabled(true);
}

double lib4774::MPU6050::PIDGet() {
    return getRotationZ();
}
