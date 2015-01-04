#ifndef MPU //not using MPU6050 as it would conflict with invensense driver
#define MPU

#include <WPILib.h>

#include "../libs/inv_mpu_dmp_motion_driver.h"
#include "../libs/inv_mpu.h"

#define MPU6050 //imu driver needs this
#define PORT 0
#define MPU6050_ADDR 0x68
#define MPU6050_WHO_AM_I 0x75
#define GPIO_INT_FILE "/sys/class/gpio/gpio14/value"
// scale factors for the data received from the imu
#define QUAT_SCALE (1.0/1073741824)
#define GYRO_SCALE (PI/(180.0*16.384))
#define ACCEL_SCALE (1.0/16384)
// the amount that the IMU Euler values have to change less than to indicate that calibration has finished
#define THRESHOLD (0.1*PI/180.0)
#define CALIBRATION_TIME 20.0

class Mpu6050: public I2C, public Subsystem {
public:
	// get information that we are getting from the mpu
	Mpu6050(); //initialize
	~Mpu6050();

	int getData();

	double GetXAccel();
	double GetYAccel();
	double GetZAccel();

	double GetXGyro();
	double GetYGyro();
	double GetZGyro();

	double GetRoll();
	double GetPitch();
	double GetYaw();

	double[] GetAccel();
	double[] GetGyro();
	double[] GetEuler();

private:
	//euler is roll, pitch, yaw, other two are x, y, z
	double[] euler, accel, gyro;

	void euler(float* q, float* euler_angles); // Convert quaternions to Euler angles
	// Functions for setting gyro/accel orientation
	unsigned short inv_row_2_scale(const signed char *row);
	unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx);
	int q_multiply(float* q1, float* q2, float* result);
	int rescale_l(long* input, float* output, float scale_factor, char length);
	int rescale_s(short* input, float* output, float scale_factor, char length);
};

#endif
