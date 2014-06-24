#include "crio.h"
#include "WPILib.h"

#define MPU_I2C_MODULE 0
#define MPU_I2C_ADDRESS MPU6050_DEFAULT_ADDRESS


#if defined MPU_I2C_MODULE && defined MPU_I2C_ADDRESS
static I2C* i2c = DigitalModule::GetInstance(MPU_I2C_MODULE)->GetI2C(MPU_I2C_ADDRESS);
#else
#error You must define MPU_I2C_MODULE and MPU_I2C_ADDRESS
#endif

void delay_ms(unsigned long num_ms) {
	Wait(num_ms / 1000.0);
}

void get_ms(unsigned long *count) {
	*count = (GetTime() * 1000);
}

void reg_int_cb(struct int_param_s *) {
	// not implemented
}

char i2c_write(unsigned char slave_addr, unsigned char reg_addr,
     unsigned char length, unsigned char const *data) {
	char retval = 0;
	for (unsigned char i=0; i<length; ++i) {
		retval += i2c->Write(reg_addr+i, data[i]);
	}
	return retval;
}
char i2c_read(unsigned char slave_addr, unsigned char reg_addr,
     unsigned char length, unsigned char *data) {
	return i2c->Read(reg_addr, length, data);
}





