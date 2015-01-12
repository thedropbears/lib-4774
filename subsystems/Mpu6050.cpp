#include "Mpu6050.h"

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <time.h>

extern "C" {
#include "../libs/drop_bone_imu.h"
}

extern float last_euler[3];
extern float quat_offset[4];
extern int fd;
extern signed char gyro_orientation[9];

unsigned long timestamp;
unsigned char more[0];
struct pollfd fdset[1];
char buf[1];

float angles[NOSENTVALS];

Mpu6050::Mpu6050(): Subsystem("Mpu6050"){
	init();
}

Mpu6050::~Mpu6050() {

}

int Mpu6050::UpdateValues() {
	int fifo_read = dmp_read_fifo(gyro, accel, quat, &timestamp, sensors, more);
	if (fifo_read != 0) {
		//printf("Error reading fifo.\n");
		return fifo_read;
	}

	rescale_l(quat, angles+9, QUAT_SCALE, 4);
	// rescale the gyro and accel values received from the IMU from longs that the
	// it uses for efficiency to the floats that they actually are and store these values in the angles array
	rescale_s(gyro, angles+3, GYRO_SCALE, 3);
	rescale_s(accel, angles+6, ACCEL_SCALE, 3);
	// turn the quaternation (that is already in angles) into euler angles and store it in the angles array
	euler(angles+9, angles);
	//printf("Yaw: %+5.1f\tPitch: %+5.1f\tRoll: %+5.1f\n", angles[0]*180.0/PI, angles[1]*180.0/PI, angles[2]*180.0/PI);
	return 0; //ok
}

void Mpu6050::Zero() {
	memcpy(quat_offset, quat, 4);
}

float Mpu6050::GetXAccel() {
	return accel[0];
}

float Mpu6050::GetYAccel() {
	return accel[1];
}

float Mpu6050::GetZAccel() {
	return accel[2];
}

float Mpu6050::GetXGyro() {
	return gyro[0];

}

float Mpu6050::GetYGyro() {
	return gyro[1];
}

float Mpu6050::GetZGyro() {
	return gyro[2];
}

float Mpu6050::GetRoll() {
	return angles[2];
}

float Mpu6050::GetPitch() {
	return angles[1];
}

float Mpu6050::GetYaw() {
	return angles[0];
}

float* Mpu6050::GetAccel() {
	return angles+6;
}

float* Mpu6050::GetGyro() {
	return angles+3;
}

float* Mpu6050::GetEuler() {
	return angles;
}
