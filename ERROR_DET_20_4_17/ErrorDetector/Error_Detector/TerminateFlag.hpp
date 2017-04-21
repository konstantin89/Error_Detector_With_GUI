/******************************************
*
* @author: Kosta Bulgakov
*
* @date: 12/09/2016
*
* @brief: Header file for inerruption flag
*         for multithreaded proces. 
*
******************************************/

#include <mutex>

/**
* Class that used by threads
* to receive signal of termination.
*
* Methods implemented in header file
* in order to make them inline.
*
*/
class TerminateFlag
{
private:
    /*
    * Flag that is on when terminate
    * command has been received.
    */
    bool _flag;
public:
    /*
    * Constructor.
    */
    TerminateFlag()
    {
        resetFlag();
    }
    /*
    * Set the termintation flag to true.
    */
    void setFlag()
    {
        _flag = true;
    }
    /*
    * Check flag status.
    */
    bool checkFlag() const
    {
        return _flag;
    }
    /*
    * Reset the termination flag.
    */
    void resetFlag()
    { 
        _flag = false;   
    }
};


























