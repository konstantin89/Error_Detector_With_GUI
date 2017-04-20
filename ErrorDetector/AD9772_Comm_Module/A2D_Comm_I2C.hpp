
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "A2D_Communication.hpp"

#include <errno.h>



/*
* Communication module for A2D device
* using I2C serial communication protocol.
*
* Note that I2C address is 7 bit number.
*
*/
class A2D_Comm_I2C: public A2D_Communication
{

protected:

	/*
	* Constructor.
	*/
	A2D_Comm_I2C();

	/*
	* Constructor.
	*/
	A2D_Comm_I2C(int deviceAddress);

	/*
	* Destructor.
	*/
	~A2D_Comm_I2C();


public:
	/*
	* Get file descriptor for communication with device.
	*/
	int openCommunicatioBus() override;

	/*
	* Initiate communicatin with the device.
	*/
	int initCommunication() override;

	/*
	* Read data from device.
	*/
	int readData(BYTE* buff, UINT bytesToRead) override;

	/*
	* Write data to device.
	*/
	int writeData(BYTE* buff, UINT bytesToWrite) override; 

private:

};
