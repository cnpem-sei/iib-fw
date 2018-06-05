/*
 * i2c_driver.h
 *
 *  Created on: 14 de ago de 2017
 *      Author: allef.silva
 */

#ifndef DRIVERS_PERIPHERAL_DRIVERS_I2C_I2C_DRIVER_H_
#define DRIVERS_PERIPHERAL_DRIVERS_I2C_I2C_DRIVER_H_

extern void InitI2C5(void);
extern void I2C5Send(uint8_t slave_addr, uint8_t num_of_args, ...);
extern uint32_t I2C5Receive(uint32_t slave_addr, uint8_t reg);

extern void InitI2C2(void);
extern void I2C2Send(uint8_t slave_addr, uint8_t num_of_args, ...);
extern uint32_t I2C2Receive(uint32_t slave_addr, uint8_t reg);

/*
extern void i2c5_init();
extern uint32_t read_i2c5_byte(uint32_t device_address, uint32_t device_register);
extern void read_i2c5_data(uint32_t device_address, uint32_t device_register, uint32_t *data, uint32_t len);
extern void write_i2c5_byte(uint32_t device_address, uint32_t device_register, uint32_t data);

extern void i2c2_init(uint32_t ui32SysClock);
extern uint32_t read_i2c2_byte(uint32_t device_address, uint32_t device_register);
extern void read_i2c2_data(uint32_t device_address, uint32_t device_register, uint32_t *data, uint32_t len);
extern void write_i2c2_byte(uint32_t device_address, uint32_t device_register, uint32_t data);

extern uint32_t read_i2c2_2byte(uint32_t device_address, uint32_t device_register);
extern void write_i2c2_2byte(uint32_t device_address, uint32_t device_register, uint32_t data);
*/

#endif /* DRIVERS_PERIPHERAL_DRIVERS_I2C_I2C_DRIVER_H_ */
