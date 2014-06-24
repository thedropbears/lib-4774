#ifndef CRIO_H_
#define CRIO_H_

#define MPU6050_ADDRESS_AD0_LOW 0xD0 // address pin low (GND), default for InvenSense evaluation board
#define MPU6050_ADDRESS_AD0_HIGH 0xD2 // address pin high (VCC)
#define MPU6050_DEFAULT_ADDRESS MPU6050_ADDRESS_AD0_LOW

#define log_i
#define __no_operation()

#ifdef __cplusplus
extern "C" {
#endif

char i2c_write(unsigned char slave_addr, unsigned char reg_addr,
     unsigned char length, unsigned char const *data);
char i2c_read(unsigned char slave_addr, unsigned char reg_addr,
     unsigned char length, unsigned char *data);
void delay_ms(unsigned long num_ms);
void get_ms(unsigned long *count);
void reg_int_cb(struct int_param_s *);
//void reg_int_cb(void (*cb)(void), unsigned char port, unsigned char pin);

#ifdef __cplusplus
}
#endif



#endif /* CRIO_H_ */
