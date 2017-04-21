/*****************************************************************
*
* @author: Kosta Bulgakov
*
* @date: 19\12\2016
*
* @brief: 
*
*****************************************************************/


/*********************** Includes *******************************/
#include <iostream>
#include "AD9772_Comm.h"
#include <chrono>

/**************** Defines for AD7992 device  *******************/
// Flag for debugging.
#define DEBUG 1

// Print samples to standard output for debugging. 
#define print_debug(val, chanel)\
            do{ if(DEBUG) printf("Value:%d, Chanel:%d\n", val, chanel);} while(0)

//Print errror to user.
#define print_error(errorText)\
            fprintf(stderr, errorText);


#define ADDRESS_AS_GND 0x23
#define CONF_REG_VAL_HEX 0x38

//Do not ommit LSB bits from samples.
#define RESULT_MASK  0xfff 


void commandMode_AD7992(int sampleDelay);
void autoMode_AD7992(int sampleDelay);


int main()
{
	int sampleDelay = 0;

	std::cout << "Enter delay between samples(microsecs)" << std::endl;
	std::cin >> sampleDelay;
	if(sampleDelay < 0)
	{
		exit(MY_ERROR);
	}
	std::cout << std::endl;

	autoMode_AD7992(sampleDelay);
	//commandMode_AD7992(sampleDelay);
	return SUCCESS;
}


void commandMode_AD7992(int sampleDelay)
{
	AD9772_Comm ad7992Comm(ADDRESS_AS_GND);
    if(ad7992Comm.openCommunicatioBus() == MY_ERROR)
    {
            std::cout << "Open communication failed" << std::endl;
    }
    if(ad7992Comm.initCommunication() == MY_ERROR)
    {
        std::cout << "Init communication failed" << std::endl;
    }
    
    if(ad7992Comm.setControlRegister(CONFIGURATION_REG, CONF_REG_VAL_HEX) 
                                                              == MY_ERROR)
    {
        std::cout << "Setting configutation register failed" << std::endl;
    }
    if(ad7992Comm.setCommandMode(COMMAND_BOTH_CH) == MY_ERROR)
    {
        std::cout << "Setting command mode failed" << std::endl;
    } 

    /*
    * Sampling loop.
    */
    while(1)
    {	
        WCHAR ch1Val, ch2Val;

	    if(ad7992Comm.readCommandMode(ch1Val, ch2Val, ADDRESS_AS_GND) 
                                                            == MY_ERROR)
        {
            continue;
        }
        else
        {
            print_debug(ch1Val, 0);
            print_debug(ch2Val, 1);
        }
        delay(sampleDelay);
    }
    return;
}



void autoMode_AD7992(int sampleDelay)
{

	AD9772_Comm ad7992Comm(ADDRESS_AS_GND);
    if(ad7992Comm.openCommunicatioBus() == MY_ERROR)
    {
        print_error("Open communication failed\n");
    }
    if(ad7992Comm.initCommunication() == MY_ERROR)
    {
        print_error("Init communication failed\n")
    }
    
    if(ad7992Comm.setControlRegister(CONFIGURATION_REG, CONF_REG_VAL_HEX) 
                                                              == MY_ERROR)
    {
        print_error("Setting configutation register failed\n");
    }
    /*
    * Start the auto sampling mode
    * by setting the sample rating 
    * interval.
    */
    if(ad7992Comm.setAutoSampleMode(Tx32) == MY_ERROR)
    {
        print_error("Set auto mode failed\n");
    }

    if(ad7992Comm.setAddrRegister(CONVERTION_RESULT_REG) == MY_ERROR)
    {
        print_error("Setting addres register failed\n");
    }
    
    WCHAR ch1Val, ch2Val;
    while(1)
    {
        if(ad7992Comm.readAutoMode(ch1Val, ch2Val, ADDRESS_AS_GND) == MY_ERROR)
        {
            continue;
        }
        else
        {
            print_debug(ch1Val, 0);
            print_debug(ch2Val, 1);
        }
		delay(sampleDelay);
	}
    return;
}


/**************************** End of file ****************************/