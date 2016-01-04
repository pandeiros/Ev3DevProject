#include "RobotModelA.h"
#include "SignalHandler.h"
#include "Communication.h"

#include <signal.h>
#include <errno.h>
#include <thread>

int main(int argc, char * argv[])
{
    ev3::Communication comm;
    ev3::RobotModelA * robot = new ev3::RobotModelA;
    ev3::MessageQueue * messageQueue = new ev3::MessageQueue;
    
    signal(SIGINT, ev3::SignalHandler::HandleSignal);
    ev3::SignalHandler::robot = robot;

//    Wrapper *w = new Wrapper();
   //std::thread robotThread = robot->createThread(messageQueue);
   std::thread communicationThread = comm.createThread(messageQueue);
   
   robot->run(messageQueue);
//   std::thread tw2 = w->member2Thread("hello", 100);
//    std::thread robotThread(&, messageQueue);
//    std::thread communicationThread(&comm.run, messageQueue);
    
    //robotThread.join();
    communicationThread.join();

    delete robot;
    delete messageQueue;

    return 0;
}