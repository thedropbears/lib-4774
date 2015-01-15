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

#include "lib-4774/commands/ReadMpu.h"

extern "C" {
#include "../libs/drop_bone_imu.h"
}

Mpu6050::Mpu6050(): Subsystem("Mpu6050"){
	init();
}

Mpu6050::~Mpu6050() {

}

void Mpu6050::InitDefaultCommand() {
  SetDefaultCommand(new ReadMpu());
}



int Mpu6050::UpdateValues() {
  long quat[4];
  unsigned char more[1];
  unsigned long timestamp;

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

	return 0; //ok
}

void Mpu6050::euler(float* q, float* euler_angles) {
    float corrected_q[4] = {0,0,0,0};
    q_multiply(quat_offset, q, corrected_q);
    euler_angles[0] = -atan2(2*corrected_q[1]*corrected_q[2] - 2*corrected_q[0]*corrected_q[3], 2*corrected_q[0]*corrected_q[0] + 2*corrected_q[1]*corrected_q[1] - 1); // psi, yaw
    euler_angles[1] = asin(2*corrected_q[1]*corrected_q[3] + 2*corrected_q[0]*corrected_q[2]); // phi, pitch
    euler_angles[2] = -atan2(2*corrected_q[2]*corrected_q[3] - 2*corrected_q[0]*corrected_q[1], 2*corrected_q[0]*corrected_q[0] + 2*corrected_q[3]*corrected_q[3] - 1); // theta, roll
}

void Mpu6050::Zero() {
  quat_offset[0] = angles[9];
  for (int i=1; i < 4; ++i) {
    quat_offset[i] = -angles[i+9];
  }
  euler(angles+9, angles);
}

float Mpu6050::GetXAccel() {
	return angles[6];
}

float Mpu6050::GetYAccel() {
	return angles[7];
}

float Mpu6050::GetZAccel() {
	return angles[8];
}

float Mpu6050::GetXGyro() {
	return angles[3];
}

float Mpu6050::GetYGyro() {
	return angles[4];
}

float Mpu6050::GetZGyro() {
	return angles[5];
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
