

#include <iostream>

#define SUCCESS 0
#define MY_ERROR -1


typedef unsigned int UINT;
typedef unsigned char BYTE;

/*
* Pure virtual class that represents 
* serial communication module with analog to
* digital converter device.
*
*/
class A2D_Communication
{
public:   



	/*
	* Constructor.
	*/
	A2D_Communication()
	{
		_deviceAddress = 0;
		_fileDescriptor = 0;
	}

	/*
	* Constructor.
	*/
	A2D_Communication(int deviceAddress)
	{
		_deviceAddress = deviceAddress;
		_fileDescriptor = 0;
	}

	/*
	* Destructor.
	*/
	virtual ~A2D_Communication()
	{
		/* EMPTY */
	}

	/*
	* Setter for the device address.
	*/
	void setAddress(int address)
	{
		_deviceAddress = address;
	}

	/*
	* Get file descriptor for communication with device.
	*/
	virtual int openCommunicatioBus() = 0;

	/*
	* Initiate communicatin with the device.
	*/
	virtual int initCommunication() = 0;

	/*
	* Read data from device.
	*/
	virtual int readData(BYTE* buff, UINT bytesToRead) = 0;

	/*
	* Write data to device.
	*/
	virtual int writeData(BYTE* buff, UINT bytesToRead) = 0; 

	int getDesc()
	{
		return _fileDescriptor;
	}


protected:

	/*
	* Address of device used.
	*/
	int _deviceAddress;

	/*
	* The file descriptor that used to read and write
	* data to the A2D device.
	*/
	int _fileDescriptor;



};
