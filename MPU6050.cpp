#include "MPU6050.h"

extern "C" {
	#include "mpu6050/dmpKey.h"
	#include "mpu6050/dmpmap.h"
	#include "mpu6050/inv_mpu.h"
	#include "mpu6050/inv_mpu_dmp_motion_driver.h"
}

lib4774::MPU6050::MPU6050() {
	run();
}

void lib4774::MPU6050::run() {
	// Intialise the MPU
    struct int_param_s int_param;
    mpu_init(&int_param);

	// Initialise the DMP
	dmp_load_motion_driver_firmware();
	dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL | DMP_FEATURE_SEND_CAL_GYRO);
	dmp_set_fifo_rate(10);

}

double lib4774::MPU6050::PIDGet() {
    dmpGetEuler(euler);
    return euler[0];
}

double lib4774::MPU6050::getRotationX() {
    dmpGetEuler(euler);
    return euler[0];
}
double lib4774::MPU6050::getRotationY() {
    dmpGetEuler(euler);
    return euler[1];
}
double lib4774::MPU6050::getRotationZ() {
    dmpGetEuler(euler);
    return euler[2];
}

unsigned char lib4774::MPU6050::dmpGetEuler(double *data) {
	unsigned long sensor_timestamp;
	short gyro[3], accel[3], sensors;
    unsigned char more;
    long quat[4];
    double euler[3];

    dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,
                    &more);
    Quaternion q = Quaternion(quat[0], quat[1], quat[2], quat[3]);

    data[0] = atan2(static_cast<double>(2*q.x*q.y - 2*q.w*q.z),
        static_cast<double>(2*q.w*q.w + 2*q.x*q.x - 1)); // psi
    data[1] = -asin(static_cast<double>(2*q.x*q.z + 2*q.w*q.y)); // theta
    data[2] = atan2(static_cast<double>(2*q.y*q.z - 2*q.w*q.x),
        static_cast<double>(2*q.w*q.w + 2*q.z*q.z - 1)); // phi
     return 0;
 }

unsigned char lib4774::MPU6050::dmpGetYawPitchRoll(double *data, Quaternion *q, VectorFloat *gravity) {
     // yaw: (about Z axis)
    data[0] = atan2(static_cast<double>(2*q -> x*q -> y - 2*q -> w*q -> z),
        static_cast<double>(2*q -> w*q -> w + 2*q -> x*q -> x - 1));
     // pitch: (nose up/down, about Y axis)
    data[1] = atan(static_cast<double>(gravity -> x
        / sqrt(gravity -> y*gravity -> y + gravity -> z*gravity -> z)));
     // roll: (tilt left/right, about X axis)
    data[2] = atan(static_cast<double>(gravity -> y
        / sqrt(gravity -> x*gravity -> x + gravity -> z*gravity -> z)));
    return 0;
 }
