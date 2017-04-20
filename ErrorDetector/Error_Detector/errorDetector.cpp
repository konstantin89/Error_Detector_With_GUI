/*************************************************
*
* @author: Kosta Bulgakov
*
* @date: 02/09/2016
*
* @brief: This file contains multithreaded real time 
*         system for human error detection.
*
*************************************************/

#include "errorDetector.h"
#include "../Graphics/GameLogic.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include "pointerLocation.h"


#include <iostream>

#define FRAME_RATE 60
#define X_POSITION 0
#define Y_POSITION 0
#define RECT_SIZE 100.f
#define SMALL_RECT_SIZE 70.f
#define RECT_MOVING_FACTOR_X 60
#define RECT_MOVING_FACTOR_Y -65
#define CHANGE_DIRECTION -1
using namespace std;

//Queue for samples to be processed.
ThreadSafeQueue<PSample> gSampleQueue;

//Queue for samples to be printed to text file.
ThreadSafeQueue<std::string> gRawDataForFileWriting;

//Conter of the number of samples that were made.
long sampleCount = 0;

//Flag that is turned on when we get termination command.
TerminateFlag gTerminateFlag;

//Signal action fot ctrl+c.
struct sigaction gSigIntHandler;

pointerLocation po;
int WindowSize = 800;



TestParameters g_testParams;

LogModule g_logModule(LOG_FILE_NAME_STR.c_str());




void autoSamplingMode()
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
    std::chrono::steady_clock::time_point timeBeforeSample;
    std::chrono::steady_clock::time_point timeAfterSample;
    while(TERMINATION_FLAG == false)
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
                sampleCount++;

                ch1Val = ch1Val & RESULT_MASK;
                ch2Val = ch2Val & RESULT_MASK;
    
                print_debug(ch1Val, 0);
                print_debug(ch2Val, 1);
    
                PSample newSample = new Sample(ch1Val, ch2Val, 
                                               timeBeforeSample);
                gSampleQueue.push(newSample);
                
                std::string logEntery = g_logModule.createLogString(ch1Val,
                                                               ch2Val, 
                                                               microSecs);

                g_logModule.pushLogEntery(logEntery);
                //gRawDataForFileWriting.push(sampleStr);
            }
            
        }
	}
    return;
}


void commandModeTwoChan()
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
    * Time points that used to calculate the time
    * between samples.
    */
    std::chrono::steady_clock::time_point timeSampleTaken;

    /*
    * Sampling loop.
    */
    while(TERMINATION_FLAG == false)
    {	
        WCHAR ch1Val, ch2Val;
       
	    timeSampleTaken = std::chrono::steady_clock::now();

	    if(ad7992Comm.readCommandMode(ch1Val, ch2Val, ADDRESS_AS_GND) 
                                                            == MY_ERROR)
        {
            continue;
        }
        else
        {
            sampleCount++;

            print_debug(ch1Val, 0);
            print_debug(ch2Val, 1);

            PSample newSample = new Sample(ch1Val, ch2Val, 
                                                   timeSampleTaken);
            gSampleQueue.push(newSample);
            
            //Save the sample as string to be written to text file.
	        std::string sampleStr = std::to_string(ch1Val) + 
                                   " " + std::to_string(ch2Val);
            gRawDataForFileWriting.push(sampleStr);
        }
        
    }
    return;
}


void AD9772_Manager()
{
    autoSamplingMode();
    //commandModeTwoChan();

    std::cout << "### Thread Done: AD9772_Manager." << std::endl;
    return;
}


void dataProcessor()
{
    int popRetVal;
    while((TERMINATION_FLAG == false) or\
          (gSampleQueue.empty() == false))
    {
        PSample popedSample;
        if(TERMINATION_FLAG == true)
        {
            popRetVal = gSampleQueue.tryToPop(popedSample);
            if (popRetVal == false)
                continue; 
        }        
        else
        {
            gSampleQueue.waitAndPop(popedSample);

            po.pushSample(*popedSample);
            
            /*
            ************* DO CALCULATION ON DATA HERE *********.
            *
            * Read the converted data and the time
            * when the sample has been taken from 
            * popedSample.
            *
            * popedSample is the sample to be processed.
            *
            */

            //After finishing working with sample, delete it.
            //delete popedSample;
        }
    }
    std::cout << "### Thread Done: dataProcessor." << std::endl;
    return;
}


void dataWriter()
{
    while(TERMINATION_FLAG == false)
    {
        while(g_logModule.tryToPop())
        {
            /* EMPTY */
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "### Thread Done: dataWriter." << std::endl;
    return;
}


void terminateThreads()
{
    //Set the termination flag to true.
    gTerminateFlag.setFlag();
    //Notify all the CV of the thread safe queues.
    gSampleQueue.notifyAll(NULL);

    gRawDataForFileWriting.notifyAll(ZERO_SAMPLE_STR);

}


void sigIntHandler(int sigNum)
{
    std::cout << "\nSignal handler called with signal number: " \
              << sigNum << std::endl;

    std::cout << "Data queue:" <<gSampleQueue.size() << std::endl;        
    terminateThreads();

    std::cout<< "File writing queue: "<<gRawDataForFileWriting.size()
             << std::endl;

    if(sigNum != SIGINT)
    {
        std::cout << "Total sample count: " << sampleCount << std::endl;
        std::cout << "Sample per second rate: " \
                  << int(sampleCount/TEST_DURATION_SECS) << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(FINISH_DELAY_SEC));
    exit(0);
}


void setSignalHandler()
{
    gSigIntHandler.sa_handler = sigIntHandler;
    sigemptyset(&gSigIntHandler.sa_mask);
    gSigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &gSigIntHandler, NULL);
}


void applicationFunc()
{
	int speedFactor = 1;
	int patternCounter = 0;
	std::string name;//(g_userName) ;
	sf::Clock clock;

	GameLogic* game = new GameLogic(1);
	po.setScreenSize(game->screenHeight);
	
	game->startClocks(clockType::dir);
	game->startClocks(clockType::size);
	game->startClocks(clockType::speed);
	
	game->changeDirection = g_testParams.directionChange;
	game->changeSpeed = g_testParams.seedChange;
	game->changeSize = g_testParams.rectSize;

	srand(time(NULL));
	bool gameInStartScreen = true;
	bool firstIteration = true;
	while (TERMINATION_FLAG == false)
	{
		//move the rectangle
		sf::Event event;
		const sf::String userName = (const sf::String)name;
		//game->setTitle(userName);
		if (firstIteration) {
			firstIteration = false;
			game->getWindow()->display();
			clock.restart();
		}
		game->checkClocks();

		sf::Time elapsed = clock.restart();
		//std::cout << elapsed.asMilliseconds() << '\n';


		float movingFactorX = elapsed.asSeconds()*RECT_MOVING_FACTOR_X *speedFactor;
		float movingFactorY = elapsed.asSeconds()*RECT_MOVING_FACTOR_Y *speedFactor;
		const sf::Vector2f & pos = game->getRect()->getPosition();
		/*checking for clocks events*/
		if (game->changeSpeed) {
			speedFactor = (rand() % (int)(5)) + 1;
		}
		if (game->changeDirection){
			game->rectInWindow();
		}

		if (!game->rectInWindow())
		{
			if (game->xIsOut) {
				float randNum = rand();
				float angleFactorX = static_cast <float> (randNum > 0 ? randNum: -randNum) / static_cast <float> (RAND_MAX);
				movingFactorX *= (angleFactorX)*10 ;
				game->changeXDirection *= CHANGE_DIRECTION;
				game->xIsOut = false;
			}
			if (game->yIsout) {
				float randNum = rand();
				float angleFactorY = static_cast <float> (randNum) / static_cast <float> (RAND_MAX);
				game->changeYDirection *= CHANGE_DIRECTION;
				movingFactorY *= (angleFactorY)*10 ;
				game->yIsout = false;
			}
		}
		
		if (game->changeSize) {
			float size = (rand() % (int)(50)) + 60;
			game->changeRectSize(size);
		}

		const float & xPos = (pos.x - movingFactorX*game->changeXDirection);
		const float & yPos = (pos.y - movingFactorY*game->changeYDirection);
		game->RectSetPosition(xPos , yPos );
		
		while (game->getWindow()->pollEvent(event))
		{
			switch (event.type)
			{
			case(sf::Event::Closed):
			sigIntHandler(0);
				game->getWindow()->close();
				
				break;
			case(sf::Event::EventType::MouseMoved)://to change to incoming semple.
				//game->getCircle()->setPosition(event.mouseMove.x, event.mouseMove.y);
				break;
			default:
				break;
			}
		}
		
		game->getCircle()->setPosition(po.getX(), po.getY()) ;
		if (game->isCollision()) {
			game->getWindow()->clear(sf::Color());
		}
		else {
			game->getWindow()->clear(sf::Color(250, 0, 0));
		}
		game->getWindow()->draw((*game->getRect()));
		game->getWindow()->draw((*game->getSmallRect()));
		game->getWindow()->draw((*game->getCircle()));
		game->getWindow()->display();
	}
    delete game;
    std::cout << "### Thread Done:applicationFunc." << std::endl;
}

int main()
{   
	
    std::cout << std::endl;
    std::cout << "#################################" << std::endl;
    std::cout << "### Welcome to Error Detector ###" << std::endl;
    std::cout << "#################################" << std::endl;
    std::cout << std::endl;
	
	if(TestParameters::paramFileExists(PARAM_FILE_NAME_STR.c_str()))
    {
        g_testParams.readParamsFromFile(PARAM_FILE_NAME_STR.c_str());
    }
    else
    {
        std::cout << "No Parameter file provided, using default values"
                  << std::endl;
    }

    g_logModule.createLogFileTitle(g_testParams);
    
    ushort calibData[4];
    if(JoystickCalib::readFromFile(calibData, CALIB_DATA_FILE.c_str()) == SUCCESS)
    {
        X_MIN = calibData[2];
        X_MAX = calibData[3];
        Y_MIN = calibData[1];
        Y_MAX = calibData[0];
    }

    std::cout << "Current app will run for "
              << std::to_string(TEST_DURATION_SECS) 
              << " seconds." << std::endl;

    std::cout << "You can terminate app by Ctrl+C."
              << std::endl;
   

    setSignalHandler();

    std::thread AD9772_ManagerThread(AD9772_Manager);
    std::thread dataProcessorThread(dataProcessor);
    std::thread dataWriterThread(dataWriter);
    std::thread gameAppThread(applicationFunc);

    AD9772_ManagerThread.detach();
    dataProcessorThread.detach();
    dataWriterThread.detach();
    gameAppThread.detach();

    std::this_thread::sleep_for(std::chrono::seconds(10000000));
    
    return 0;
}

/********************** End of file ***************************/



















