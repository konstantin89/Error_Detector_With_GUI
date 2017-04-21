/**************************************************
*
* @author: Kosta Bulgakov
*
* @date: 02/09/2016
*
* @brief: Header file for thread safe queue class.
*         Since the class uses templates, its
*         implemented in the header..
*
**************************************************/

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#ifndef THREAD_Q
#define THREAD_Q

template<typename T>
/*
* Wrapper class for queue.
*/
class ThreadSafeQueue
{
private:
    /*
    * Mutex for the thread safety.
    */
    mutable std::mutex mut;
    /*
    * The queue that will contain the data.
    */
    std::queue<T> dataQueue;
    /*
    * Condition variable for data extracting.
    */
    std::condition_variable cond;
public:
    /*
    * Constructor.
    */
    ThreadSafeQueue()
    {
        //Empty
    }

    /*
    * Copy constructor.
    */
    ThreadSafeQueue(ThreadSafeQueue const& paramQueue)
    {
        std::lock_guard<std::mutex> lk(paramQueue.mut);
        dataQueue = paramQueue.dataQueue;
    }

    /*
    * Push data in to the queue.
    */
    void push(T dataToPush)
    {
        std::lock_guard<std::mutex> lk(mut);
        dataQueue.push(dataToPush);
        cond.notify_one();
    }

    /*
    * Wait until there is value to pop and pop.
    */
    void waitAndPop(T& returnedData)
    {
        std::unique_lock<std::mutex> lk(mut);
        cond.wait(lk, [this]{return !dataQueue.empty();});
        returnedData = dataQueue.front();
        dataQueue.pop();
    }

    /*
    * Implementation for specific type GpioSample.
    *
    * Wait until there is value to pop and pop.
    * 
    
    void waitAndPop(GpioSample& returnedData)
    {
        GpioSample popedSample;
        std::unique_lock<std::mutex> lk(mut);
        cond.wait(lk, [this]{return !dataQueue.empty();});
        popedSample = dataQueue.front();
        returnedData.setXY(popedSample.getX(), popedSample.getY());
        dataQueue.pop();
    }*/

    /*
    * Try to pop data from the queue.
    */
    bool tryToPop(T& returnedData)
    {  
        std::lock_guard<std::mutex> lk(mut);
        if(dataQueue.empty())
        {
            return false;
        }
        else
        {
            returnedData = dataQueue.front();
            dataQueue.pop();
            return true;
        }
    }

    /*
    * Check if the queue is empty.
    */
    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mut);
        return dataQueue.empty();
    }

    /*
    * Get the queue size.
    */
    unsigned int size() const
    {
        std::lock_guard<std::mutex> lk(mut);
        return dataQueue.size();
    }  

    /*
    * Method that used to wake up all the 
    * threads that are waiting for CV for this
    * queue.
    */
    void notifyAll(T zeroToPush)
    {
        //std::lock_guard<std::mutex> lk(mut);
        dataQueue.push(zeroToPush);
        cond.notify_all();
    }
};
#endif



































