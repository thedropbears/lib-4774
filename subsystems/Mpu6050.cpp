#include "Mpu6050.h"

#include "lib-4774/commands/ReadMpu.h"

extern "C" {
#include "../mpu6050/mpu_functions.h"
}

I2C* Mpu6050::i2c = NULL;

int i2c_write(unsigned char slave_addr, unsigned char reg_addr,
        unsigned char length, unsigned char const *data){
    unsigned char tmp[length+1];
    tmp[0] = reg_addr;
    memcpy(tmp+1, data, length);
    return Mpu6050::i2c->WriteBulk(tmp, length + 1);
}
int i2c_read(unsigned char slave_addr, unsigned char reg_addr,
        unsigned char length, unsigned char *data){
    return Mpu6050::i2c->Transaction(&reg_addr, 1, data, length);
}

Mpu6050::Mpu6050(I2C::Port port): Subsystem("Mpu6050"){
    i2c = new I2C(port, MPU6050_ADDR);
    init();
}

Mpu6050::~Mpu6050() {

}

void Mpu6050::InitDefaultCommand() {
    SetDefaultCommand(new ReadMpu(this));
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

double Mpu6050::PIDGet() {
    return static_cast<double>(GetYaw());
}
