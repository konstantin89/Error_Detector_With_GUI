


#include "A2D_Comm_I2C.hpp"



A2D_Comm_I2C::A2D_Comm_I2C() : A2D_Communication()
{
	/* EMPTY */
}


A2D_Comm_I2C::A2D_Comm_I2C(int deviceAddress) : A2D_Communication(deviceAddress) 
{
	/* EMPTY*/
}

A2D_Comm_I2C::~A2D_Comm_I2C()
{
	if(_fileDescriptor)
	{
		close(_fileDescriptor);
	}
}

int A2D_Comm_I2C::openCommunicatioBus()
{
	if(_fileDescriptor)
	{
		close(_fileDescriptor);
	}
	char I2C_Device_Name[40] = "/dev/i2c-1";
	_fileDescriptor = open(I2C_Device_Name, O_RDWR);
	if(_fileDescriptor < 0)
	{
		std::cout << "open() failed" << std::endl;
		return MY_ERROR;
	}
	return SUCCESS;
}

int A2D_Comm_I2C::initCommunication()
{
    if(ioctl(_fileDescriptor, I2C_SLAVE, _deviceAddress) < 0)
	{
		std::cout << "ioctl() failed. Failed to gain bus access"
		          << std::endl;
		return MY_ERROR;
	}
	return SUCCESS;
}

int A2D_Comm_I2C::readData(BYTE* buff, UINT bytesToRead)
{
	if(bytesToRead < 1)
	{
		return SUCCESS;
	}
	UINT bytesReaded = read(_fileDescriptor, buff, bytesToRead);
	
	
	if(bytesReaded < 1)
	{
		return MY_ERROR;
	}
	else
	{
		return bytesReaded;
	}
}

int A2D_Comm_I2C::writeData(BYTE* buff, UINT bytesToWrite)
{
	if(bytesToWrite < 1)
	{
		return SUCCESS;
	}
	int writenByteNum = write(_fileDescriptor, buff, bytesToWrite);	
	
	if(writenByteNum < 1)
	{
		std::cout << "write failed with error: " << errno << std::endl;
		return MY_ERROR;
	}
	else
	{
		return writenByteNum;
	}
}


