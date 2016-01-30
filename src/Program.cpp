#include "RobotModelA.h"
#include "SignalHandler.h"
#include "Communication.h"  
#include "Utils.h"
#include "Devices.h"
#include "Logger.h"

#include <signal.h>
#include <errno.h>
#include <thread>

int main(int argc, char * argv[])
{
    std::srand(std::time(0));
    auto logger = ev3::Logger::getInstance();
    
    /* Acquire parameters in specific order in case one was provided. */
    if (argc > 3)
    {
        logger->log(ev3::ERR_WRONG_NO_OF_ARGS, 
                    ev3::Logger::ERROR, ev3::Logger::STD_OUT);
        return -1;
    }
    
    if (argc > 2)
    {
        
    }
    
    std::string mode = "";

    if (argc > 1)
    {
        mode = std::string(argv[1]);
    }
    
    
    logger->setLogLevel(ev3::Logger::VERBOSE);
    logger->setLogOutput(ev3::Logger::STD_OUT);
    logger->log("TEST", ev3::Logger::VERBOSE);
    logger->log("TEST", ev3::Logger::INFO);
    logger->log("TEST", ev3::Logger::WARNING);
    logger->log("TEST", ev3::Logger::ERROR);
    
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
        logger->log(ev3::ERR_WRONG_MODE, 
                    ev3::Logger::ERROR, ev3::Logger::STD_OUT);
        return -1;
    }
    
    logger->log("Exiting...", ev3::Logger::INFO);
    
    ev3::Devices::destroy();
    ev3::Logger::destroy();
    
    return 0;
}