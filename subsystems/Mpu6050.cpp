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

Mpu6050::Mpu6050(): Subsystem("Mpu6050"){

}

Mpu6050::~Mpu6050() {

}

int Mpu6050::getData() {
	// get the data over i2c
}

int Mpu6050::open_bus() {
    if ((fd = open(BBB_I2C_FILE, O_RDWR)) < 0) {
        /* ERROR HANDLING: you can check errno to see what went wrong */
        perror("Failed to open the i2c bus");
        return 1;
    }
    if (ioctl(fd, I2C_SLAVE, MPU6050_ADDR) < 0) {
        perror("Failed to acquire bus access and/or talk to slave.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        return 1;
    }
    return 0;
}

// multiply two quaternions
int Mpu6050::q_multiply(float* q1, float* q2, float* result) {
    float tmp[4];
    tmp[0] = q1[0]*q2[0] - q1[1]*q2[1] - q1[2]*q2[2] - q1[3]*q2[3];
    tmp[1] = q1[0]*q2[1] + q1[1]*q2[0] + q1[2]*q2[3] - q1[3]*q2[2];
    tmp[2] = q1[0]*q2[2] - q1[1]*q2[3] + q1[2]*q2[0] + q1[3]*q2[1];
    tmp[3] = q1[0]*q2[3] + q1[1]*q2[2] - q1[2]*q2[1] + q1[3]*q2[0];
    memcpy(result, tmp, 4*sizeof(float));
    return 0;
}

// rescale an array of longs by scale factor into an array of floats
int Mpu6050::rescale_l(long* input, float* output, float scale_factor, char length) {
    int i;
    for(i=0;i<length;++i)
        output[i] = input[i] * scale_factor;
    return 0;
}

// rescale an array of shorts by scale factor into an array of floats
int Mpu6050::rescale_s(short* input, float* output, float scale_factor, char length) {
    int i;
    for(i=0;i<length;++i)
        output[i] = input[i] * scale_factor;
    return 0;
}

void Mpu6050::delay_ms(unsigned long num_ms){

}
void Mpu6050::get_ms(unsigned long *count){

}
void Mpu6050::reg_int_cb(struct int_param_s *param){

}

inline int min ( int a, int b ){
    return a < b ? a : b;
}
inline void __no_operation(){

}

void euler(float* q, float* euler_angles) {
    euler_angles[0] = -atan2(2*q[1]*q[2] - 2*q[0]*q[3], 2*q[0]*q[0] + 2*q[1]*q[1] - 1); // psi, yaw
    euler_angles[1] = asin(2*q[1]*q[3] + 2*q[0]*q[2]); // phi, pitch
    euler_angles[2] = -atan2(2*q[2]*q[3] - 2*q[0]*q[1], 2*q[0]*q[0] + 2*q[3]*q[3] - 1); // theta, roll
}

// Functions for setting gyro/accel orientation
unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}

unsigned short inv_orientation_matrix_to_scalar(
        const signed char *mtx)
{
    unsigned short scalar;

    /*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
     */

    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;


    return scalar;
}

double Mpu6050::GetXAccel() {
	return accel[0];
}

double Mpu6050::GetYAccel() {
	return accel[1];
}

double Mpu6050::GetZAccel() {
	return accel[2]
}

double Mpu6050::GetXGyro() {
	return gyro[0];

}

double Mpu6050::GetYGyro() {
	return gyro[1];
}

double Mpu6050::GetZGyro() {
	return gyro[2];
}

double Mpu6050::GetRoll() {
	return euler[0];
}

double Mpu6050::GetPitch() {
	return euler[1];
}

double Mpu6050::GetYaw() {
	return euler[2];
}

double* Mpu6050::GetAccel() {
	return accel;
}

double* Mpu6050::GetGyro() {
	return gyro;
}

double* Mpu6050::GetEuler() {
	return euler_angles;
}
