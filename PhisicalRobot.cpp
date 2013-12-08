
#include "PhisicalRobot.h"
//#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sstream>

#include <cmath>
#include <ctime>
//#include <stdlib.h>
using namespace PhisicalRobot;

Robot::Robot()
{
    port = "";
    fd = -1;
}

Robot::~Robot() 
{
    close_port();
}

int Robot::moveForward()
{
    return write_on_port("F");
}

int Robot::moveBackwards()
{
    return write_on_port("B");
}
int Robot::moveLeft()
{
    return write_on_port("L");
}
int Robot::moveRight()
{
    return write_on_port("R");
}
int Robot::moveForwardLeft()
{
    return write_on_port("G");
}
int Robot::moveForwardRight()
{
    return write_on_port("I");
}
int Robot::moveBackLeft()
{
    return write_on_port("H");
}
int Robot::moveBackRight()
{
    return write_on_port("J");
}
int Robot::stop()
{
    return write_on_port("S");
}
int Robot::frontLightsOn(bool state)
{
    if(state)
    {
        return write_on_port("W");     
    }
    return write_on_port("w");
    
}
int Robot::alertState(bool state)
{
    if(state)
    {
        return write_on_port("U");
    }
    return write_on_port("u");
}
int Robot::changeSpeed(unsigned int speed)
{
    speed = floor(speed);
//    std::cout << "speed = " << speed << std::endl;
    //beautiful stuff here
    std::ostringstream ostr;//create a stream for string
    ostr << speed;//put the speed on the stream
//    std::cout << "speedStream = " << ostr.str() << std::endl;
    if(speed < 10)
    {
        return write_on_port(ostr.str().c_str());//get the string on the stream and
        //converts into const char*
    }
    if(speed <= 10)
    {
        return write_on_port("q");
    }
    return write_on_port("0");//in case of a weird bug happens
    
    
}//multiples of 10
int Robot::Rotate90AntiClockwise()
{
    return write_on_port("A");
}

int Robot::Rotate90Clockwise()
{
    return write_on_port("C");
}

void Robot::test(const char* serial_port)
{
        Robot myRobot;

    if (myRobot.open_port(serial_port))
    {
        
        myRobot.moveForward();
        sleep(1);
        myRobot.moveBackwards();
        sleep(1);
        myRobot.moveLeft();
        sleep(1);
        myRobot.moveRight();
        sleep(1);
        myRobot.moveForwardLeft();
        sleep(1);
        myRobot.moveForwardRight();
        sleep(1);
        myRobot.stop();
        sleep(1);
        myRobot.frontLightsOn(true);
        sleep(1);
        myRobot.alertState(true);
        sleep(1);
        myRobot.Rotate90AntiClockwise();
        sleep(1);
        myRobot.Rotate90Clockwise();
        sleep(1);
        myRobot.frontLightsOn(false);
        sleep(1);
        myRobot.alertState(false);
        sleep(1);
        
        char *buf;
        
        if(myRobot.read_from_port(buf))
            std::cout << buf << std::endl;
        
        for(int i = 0; i <= 11; i++)
        {
           myRobot.changeSpeed(i);
           sleep(1);
        }  
    }
    else
    {
        std::cout << "FAILED TO OPEN THE PORT " << serial_port << std::endl;
    }
    
    myRobot.close_port();
}
