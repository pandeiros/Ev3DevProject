#include "RobotModelA.h"
#include "SignalHandler.h"
#include "Communication.h"  
#include "Utils.h"
#include "Devices.h"

#include <signal.h>
#include <errno.h>
#include <thread>

int main(int argc, char * argv[])
{
    std::srand(std::time(0));
    
    /* Acquire parameters in specific order in case one was provided. */
    if (argc > 2)
    {
        std::cout << ev3::ERR_WRONG_NO_OF_ARGS;
        return -1;
    }  
    
    std::string mode = "";

    if (argc > 1)
    {
        mode = std::string(argv[1]);
    }
    
    if (mode == ev3::MODE_MASTER)
    {
        ev3::Communication comm;
        ev3::Master master;
        
        signal(SIGINT, ev3::SignalHandler::HandleSignal);
        ev3::SignalHandler::master = &master;
        
        ev3::Queue<ev3::Message> * sendQueue = new ev3::Queue<ev3::Message>;
        ev3::Queue<ev3::Message> * receiveQueue = new ev3::Queue<ev3::Message>;
        std::thread communicationThread = comm.createThread(sendQueue, receiveQueue, true);
   
        // MIND SWITCHED QUEUES!
        master.run(receiveQueue, sendQueue);
  
        communicationThread.join();
        
        delete sendQueue;
        delete receiveQueue;
    }
    else if (mode == ev3::MODE_AGENT || mode == "")
    {
        ev3::Communication comm;
        ev3::RobotModelA * robot = new ev3::RobotModelA;
    
        signal(SIGINT, ev3::SignalHandler::HandleSignal);
        ev3::SignalHandler::robot = robot;
        
        ev3::Queue<ev3::Message> * sendQueue = new ev3::Queue<ev3::Message>;
        ev3::Queue<ev3::Message> * receiveQueue = new ev3::Queue<ev3::Message>;
        std::thread communicationThread = comm.createThread(sendQueue, receiveQueue);
   
        // MIND SWITCHED QUEUES!
        robot->run(receiveQueue, sendQueue);
  
        communicationThread.join();

        delete robot;
        delete sendQueue;
        delete receiveQueue;
    }
    else
    {
        std::cout << ev3::ERR_WRONG_MODE;
        return -1;
    }
    
    ev3::Devices::destroy();
    
    return 0;
}