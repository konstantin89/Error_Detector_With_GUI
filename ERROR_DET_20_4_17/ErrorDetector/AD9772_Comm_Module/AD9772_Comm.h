
#ifndef _AD9772_COMM_H
#define _AD9772_COMM_H

#include "A2D_Comm_I2C.hpp"
#include <wiringPi.h>
#include <map>
#include <thread>
#include <chrono>
#include <stdio.h>


/////////////AD9772 registers ////////////////////
#define CONVERTION_RESULT_REG 0x00
#define CONFIGURATION_REG 0x02
#define CYCLE_TIMER_REGISTER 0x03

#define ALERT_STATUS_REG 0x01

#define DATA_LOW_CH1_REG 0x04 
#define DATA_HIGH_CH1_REG 0x05

#define DATA_LOW_CH2_REG 0x07
#define DATA_HIGH_CH2_REG 0x08
//////////////////////////////////////////////////

#define CHANEL_1 0
#define CHANEL_2 1
#define INVALID_CHANEL 66

/////////////////////////////////////////////////

#define COMMAND_NO_CON 0x00
#define COMMAND_CH_1 0x10
#define COMMAND_CH_2 0x20
#define COMMAND_BOTH_CH 0x30

/////////////////////////////////////////////////

#define CONVST_PIN 14

/////////////////////////////////////////////////
enum ConversRate{NOT_AUTO, Tx32, Tx64, Tx128, Tx256,
	                    Tx512, Tx1024, Tx2048};

/////////////////////////////////////////////////
#define I2C_M_TEN           0x0010
#define I2C_M_RD            0x0001
#define I2C_M_NOSTART       0x4000
#define I2C_M_REV_DIR_ADDR  0x2000
#define I2C_M_IGNORE_NAK    0x1000
#define I2C_M_NO_RD_ACK     0x0800
#define I2C_M_RECV_LEN      0x0400

struct i2c_msg {
  __u16 addr;
  __u16 flags;
  __u16 len;
  __u8 * buf;
}; 

/////////////////////////////////////////////////

/*
* 2 byte variable to hold the conversion
* value from AD9772.
*/
typedef unsigned short WCHAR;

/*
* Class that represens communication module for
* AD9772 A2D converter chip.
*
*/
class AD9772_Comm : public A2D_Comm_I2C
{

public:


	/*
	* Container that maps convertsion rate to the value that represents
	* it in the AD9772 cycle timer register.
	*
	*/
	std::map<ConversRate, BYTE> ConvertionRateMap = {{NOT_AUTO, 0x0},
                        {Tx32, 0x1}, {Tx64, 0x2}, {Tx128, 0x3}, 
                        {Tx256, 0x4}, {Tx512, 0x5}, {Tx1024, 0x6}, 
                        {Tx2048, 0x7}};

	AD9772_Comm(int devAddress);

	/*
	* Set value to control register.
	*
	* 
	* @param: regAddress: the address of the targer register.
	* @param: regValue: the value to be set in the register.
	*
	* @return: SUCCESS or MY_ERROR.
	*/
	int setControlRegister(BYTE regAddress, BYTE regValue);

	/*
	* Set the value of address register.
	*
	* @param: regAddress: the address to be set in the address register.
	*
	* @return: SUCCESS or MY_ERROR.
	*/
	int setAddrRegister(BYTE regAddress);

	/*
	* Read value from register.
	*
	* @param: retBuf: the buffer tht will contain the output.
	* @param: bytesToRead: number of bytes to read from register.
	*
	* @return: SUCCESS or MY_ERROR.
	*
	*/
	int readRegister(BYTE* retBuf, int bytesToRead);

	/*
	* Set the AD9772 to auto sampling mode.
	*
	* @param: rate: the rate of the auto sampling.
	* 
	* @return: SUCCESS or MY_ERROR.
	*
	*/
	int setAutoSampleMode(ConversRate rate);

	/*
	*
	*
	*
	*/
	int setCommandMode(BYTE chanelToSample);

	/*
	*
	*
	*
	*
	*
	*/
	int readCommandMode(WCHAR &ch1Val, WCHAR &ch2Val, BYTE devAdr);

	/*
	*
	*
	*
	*
	*/
	int readAutoMode(WCHAR &ch1Val, WCHAR &ch2Val, BYTE devAdr);
		

	/*
	*
	*
	*
	*/
	int parseIoctlBuffer(WCHAR &ch1Val, WCHAR &ch2Val, BYTE buf[]);

};

#endif
