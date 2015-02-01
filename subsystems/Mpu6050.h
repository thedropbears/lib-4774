#ifndef MPU //not using MPU6050 as it would conflict with invensense driver
#define MPU

#include <WPILib.h>

#define MPU6050 //imu driver needs this
#define PORT 0
#define MPU6050_ADDR 0x68
#define MPU6050_WHO_AM_I 0x75
// scale factors for the data received from the imu
#define QUAT_SCALE (1.0/1073741824)
#define GYRO_SCALE (PI/(180.0*16.384))
#define ACCEL_SCALE (1.0/16384)
// the amount that the IMU Euler values have to change less than to indicate that calibration has finished
#define THRESHOLD (0.1*PI/180.0)

class Mpu6050: public Subsystem, public PIDSource {
public:
	// get information that we are getting from the mpu
	Mpu6050(); //initialize
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


private:
	//euler is roll, pitch, yaw, other two are x, y, z
    short accel[3], gyro[3], sensors[1];
    long quat[4];

    float quat_offset[4] = {1.0, 0.0, 0.0, 0.0};

    float angles[13];

    void euler(float* q, float* euler_angles);
};
#endif
