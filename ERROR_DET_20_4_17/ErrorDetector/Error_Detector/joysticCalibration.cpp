
#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errorDetector.h" 
#include "ThreadSafeQueue.hpp"
#include "../AD9772_Comm_Module/AD9772_Comm.h"
#include "Sample.h"




#define CORRECT_ARG_NUM 3

int main(int argc, char** argv)
{
	int sampleNumParam = 0;
	int delayMicros = 0;

	if(argc != CORRECT_ARG_NUM)
	{
		std::cout << "Usage: joysticCalibration SAMPLE_NUM DELAY" 
		          << std::endl;
		return MY_ERROR;
	}
	else
	{
		sampleNumParam = atoi(argv[1]);
		delayMicros = atoi(argv[2]);
	}

	int sampleCounter = 0;

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
    std::chrono::steady_clock::time_point timeBeforeSample;
    std::chrono::steady_clock::time_point timeAfterSample;
    while(sampleCounter < sampleNumParam)
    {
        timeBeforeSample = std::chrono::steady_clock::now();
        if(ad7992Comm.readAutoMode(ch1Val, ch2Val, ADDRESS_AS_GND) == MY_ERROR)
        {
            continue;
        }
        else
        {
            timeAfterSample = std::chrono::steady_clock::now();
            auto sampleDuration = timeAfterSample - timeBeforeSample;
            auto microSecs = std::chrono::duration_cast<std::chrono::microseconds>
                                                           (sampleDuration).count();

            /*
            * If the sample took too much time, we had contex switch
            * (thread switch) that makes out time measurments be
            * inaccurate. In this case we ignore the mesurment.
            *
            */
            if(microSecs > MAX_MEASURMENT_TIME_MICRO)
            {
                continue;
            }
            else
            {
                sampleCounter++;

                ch1Val = ch1Val & RESULT_MASK;
                ch2Val = ch2Val & RESULT_MASK;
    
   				std::cout << ch1Val << "," << ch2Val << std::endl;
   				std::this_thread::sleep_for(
   					           std::chrono::microseconds(delayMicros));
   			}
   		}
   	}

}