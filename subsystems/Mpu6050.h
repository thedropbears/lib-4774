#ifndef MPU //not using MPU6050 as it would conflict with invensense driver
#define MPU

#include <WPILib.h>

#include "../commands/InterruptTrigger.h"

#define MPU6050 //imu driver needs this
#define PORT 0
#define MPU6050_ADDR 0x68
#define MPU6050_WHO_AM_I 0x75

class Mpu6050: public Subsystem, public PIDSource {
public:
	// get information that we are getting from the mpu
	Mpu6050(I2C::Port, DigitalInput* di=NULL); //initialize
	~Mpu6050();

	void InitDefaultCommand();

	float GetXAccel();
	float GetYAccel();
	float GetZAccel();

	float GetXGyro();
	float GetYGyro();
	float GetZGyro();

	float GetRoll();
	float GetPitch();
	float GetYaw();

	float* GetAccel();
	float* GetGyro();
	float* GetEuler();

	int UpdateValues(); //
	void Zero(); //reset the quaternion offset
	double PIDGet();

    static I2C* i2c;

private:
	//euler is roll, pitch, yaw, other two are x, y, z
    short accel[3], gyro[3], sensors[1];
    long quat[4];

    float quat_offset[4] = {1.0, 0.0, 0.0, 0.0};

    float angles[13];

    void euler(float* q, float* euler_angles);

    DigitalInput* di;
    InterruptTrigger* interrupt;
};
#endif
