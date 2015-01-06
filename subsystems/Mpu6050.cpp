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
#include "../libs/drop_bone_imu.h"

extern float last_euler[3];
extern float quat_offset[4];
extern int fd;
extern signed char gyro_orientation[9];

Mpu6050::Mpu6050(): Subsystem("Mpu6050"){
	init();
    unsigned long timestamp;
	unsigned char more[0];
	struct pollfd fdset[1];
	char buf[1];

	// File descriptor for the GPIO interrupt pin
	int gpio_fd = open(GPIO_INT_FILE, O_RDONLY | O_NONBLOCK);

	// Create an event on the GPIO value file
	memset((void*)fdset, 0, sizeof(fdset));
	fdset[0].fd = gpio_fd;
	fdset[0].events = POLLPRI;
	time_t sec, current_time; // set to the time before calibration

	time(&sec);
	printf("Read system time\n");
	printf("Calibrating\n");

	while (1){
		// Blocking poll to wait for an edge on the interrupt
		poll(fdset, 1, -1);

		if (fdset[0].revents & POLLPRI) {
			// Read the file to make it reset the interrupt
				read(fdset[0].fd, buf, 1);

			int fifo_read = dmp_read_fifo(gyro, accel, quat, &timestamp, sensors, more);
			if (fifo_read != 0) {
				//printf("Error reading fifo.\n");
				continue;
			}

			float angles[NOSENTVALS];
			rescale_l(quat, angles+9, QUAT_SCALE, 4);

			if (!quat_offset[0]) {
				advance_spinner(); // Heartbeat to let the user know we are running"
				euler(angles+9, angles); // Determine calibration based on settled Euler angles
				// check if the IMU has finished calibrating
				time(&current_time);
				// check if more than CALIBRATION_TIME seconds has passed since calibration started
				if((fabs(last_euler[0]-angles[0]) < THRESHOLD
						&& fabs(last_euler[1]-angles[1]) < THRESHOLD
						&& fabs(last_euler[2]-angles[2]) < THRESHOLD)
						|| difftime(current_time, sec) > CALIBRATION_TIME) {
					printf("\nCALIBRATED! Threshold: %f Elapsed time: %f\n", CALIBRATION_TIME, difftime(current_time, sec));
					printf("CALIBRATED! Threshold: %.5f Errors: %.5f %.5f %.5f\n", THRESHOLD, fabs(last_euler[0]-angles[0]), last_euler[1]-angles[1], last_euler[2]-angles[2]);
					// the IMU has finished calibrating
					int i;
					quat_offset[0] = angles[9]; // treat the w value separately as it does not need to be reversed
					for(i=1;i<4;++i){
						quat_offset[i] = -angles[i+9];
					}
				}
				else {
					memcpy(last_euler, angles, 3*sizeof(float));
				}
			}
			else {
				q_multiply(quat_offset, angles+9, angles+9); // multiply the current quaternstion by the offset caputured above to re-zero the values
				// rescale the gyro and accel values received from the IMU from longs that the
				// it uses for efficiency to the floats that they actually are and store these values in the angles array
				rescale_s(gyro, angles+3, GYRO_SCALE, 3);
				rescale_s(accel, angles+6, ACCEL_SCALE, 3);
				// turn the quaternation (that is already in angles) into euler angles and store it in the angles array
				euler(angles+9, angles);
				//printf("Yaw: %+5.1f\tPitch: %+5.1f\tRoll: %+5.1f\n", angles[0]*180.0/PI, angles[1]*180.0/PI, angles[2]*180.0/PI);
				// send the values in angles over UDP as a string (in udp.c/h)
				udp_send(angles, 13);
			}
		}
	}
}

Mpu6050::~Mpu6050() {
}

double Mpu6050::GetXAccel() {
	return accel[0];
}

double Mpu6050::GetYAccel() {
	return accel[1];
}

double Mpu6050::GetZAccel() {
	return accel[2];
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
