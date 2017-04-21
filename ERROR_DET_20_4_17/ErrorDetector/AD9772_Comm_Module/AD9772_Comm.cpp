
#include "AD9772_Comm.h"


AD9772_Comm::AD9772_Comm(int devAddress) : A2D_Comm_I2C(devAddress)
{
	/* EMPTY */
}


int AD9772_Comm::setControlRegister(BYTE regAddress, BYTE regValue)
{
	int writeRetVal;
	BYTE buffer[2];
	
	buffer[0] = regAddress;
	buffer[1] = regValue;
	writeRetVal = writeData(buffer, 2);

	if(writeRetVal == 2)
	{
		return SUCCESS;
	}
	else
	{
		return MY_ERROR;
	}
}


int AD9772_Comm::setAddrRegister(BYTE regAddress)
{
	int writeRetVal;
	BYTE buffer[1];

	buffer[0] = regAddress;

	writeRetVal = writeData(buffer, 1);

	if(writeRetVal == 1)
	{
		return SUCCESS;
	}
	else
	{
		return MY_ERROR;
	}
}

int AD9772_Comm::readRegister(BYTE* retBuf, int bytesToRead)
{
	return readData(retBuf, bytesToRead);
}


int AD9772_Comm::setAutoSampleMode(ConversRate rate)
{
	return setControlRegister(CYCLE_TIMER_REGISTER, ConvertionRateMap[rate]);
}

int AD9772_Comm::setCommandMode(BYTE chanelToSample)
{
	int writeRetVal;
	BYTE buf[1];
	buf[0] = chanelToSample;
	writeRetVal = writeData(buf, 1);
	return writeRetVal;
}


int AD9772_Comm::readCommandMode(WCHAR &ch1Val, WCHAR &ch2Val, BYTE devAdr)
{

		ch1Val = 0;
		ch2Val = 0;

        struct i2c_rdwr_ioctl_data ioctlMsg;
        struct i2c_msg msg [2];
        
        BYTE writeBuf[1];
        BYTE readBuf [6];

        writeBuf[0] = 0x30;
        
        msg[0].addr = devAdr;
        msg[0].flags = 0; //write
        msg[0].len = 1;
        msg[0].buf = writeBuf;
        
        msg[1].addr = devAdr;
        msg[1].flags = 1; //?read?
        msg[1].len = 6;
        msg[1].buf = readBuf;
        
        ioctlMsg.msgs = msg;
        ioctlMsg.nmsgs = 2;
        
        int deviceDescriptor = getDesc();

        if(ioctl(deviceDescriptor ,  I2C_RDWR, &ioctlMsg) < SUCCESS)
        {
          std::cout << "ioctl failed" << std::endl;
          return MY_ERROR;
        }

        if(parseIoctlBuffer(ch1Val, ch2Val, readBuf) == MY_ERROR)
    	{
    		return MY_ERROR;
    	}
    	return SUCCESS;
}




int AD9772_Comm::readAutoMode(WCHAR &ch1Val, WCHAR &ch2Val, BYTE devAdr)
{
	ch1Val = 0;
	ch2Val = 0;

	struct i2c_rdwr_ioctl_data ioctlMsg;
    struct i2c_msg msg [2];
    
    BYTE readBuf [6];
    
    msg [0].addr = devAdr;
    msg [0].flags = I2C_M_RD;
    msg [0].len = 6;
    msg [0].buf = readBuf;

    ioctlMsg.msgs = msg;
    ioctlMsg.nmsgs = 1;
    
    int deviceDescriptor = getDesc();

    if(ioctl(deviceDescriptor ,  I2C_RDWR, &ioctlMsg) < SUCCESS)
    {
      std::cout << "ioctl failed" << std::endl;
      return MY_ERROR;
    }

    if(parseIoctlBuffer(ch1Val, ch2Val, readBuf) == MY_ERROR)
    {
    	return MY_ERROR;
    }
    return SUCCESS;
}

/*
*
*
*/
int AD9772_Comm::parseIoctlBuffer(WCHAR &ch1Val, WCHAR &ch2Val, BYTE buf[6])
{
	if((16 & buf[0]) % 15 == CHANEL_1 && (16 & buf[2]) % 15 == CHANEL_2)
    {
    	ch1Val = buf[1] + (buf[0] & 0x0f) * 256;
    	ch2Val = buf[3] + (buf[2] & 0x0f) * 256;
    }
    else if((16 & buf[0]) % 15 == CHANEL_2 && (16 & buf[2]) % 15 == CHANEL_1)
    {
    	ch1Val = buf[3] + (buf[2] & 0x0f) * 256;
    	ch2Val = buf[1] + (buf[0] & 0x0f) * 256;
    }

    else if((16 & buf[0]) % 15 == CHANEL_1 && (16 & buf[4]) % 15 == CHANEL_2)
    {
    	ch1Val = buf[1] + (buf[0] & 0x0f) * 256;
    	ch2Val = buf[5] + (buf[4] & 0x0f) * 256;
    }
    else if((16 & buf[0]) % 15 == CHANEL_2 && (16 & buf[4]) % 15 == CHANEL_1)
    {
    	ch2Val = buf[1] + (buf[0] & 0x0f) * 256;
    	ch1Val = buf[5] + (buf[4] & 0x0f) * 256;
    }
    else
    {
    	return MY_ERROR;
    }
    return SUCCESS;
}