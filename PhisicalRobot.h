/* 
 * File:   Robot.h
 * Author: bruno
 *
 * Created on November 15, 2013, 3:33 PM
 */

#ifndef PHISICAL_ROBOT_H
#define	PHISICAL_ROBOT_H
#include "Serial.h"
#include <string>

namespace PhisicalRobot{
class Robot: public Serial {
public:
    Robot();
    virtual ~Robot();
    int moveForward();
    int moveBackwards();
    int moveLeft();
    int moveRight();
    int moveForwardLeft();
    int moveForwardRight();
    int moveBackLeft();
    int moveBackRight();
    int stop();
    int frontLightsOn(bool state);//W, w
    int alertState(bool state);//the robot stays red if the state is true
    int changeSpeed(unsigned int speed);//multiples of 10
    
    
    int Rotate90Clockwise();
    int Rotate90AntiClockwise();
    
    static void test(const char* serial_port);
    
private:
    

};
}

#endif	/* ROBOT_H */
//Forward---------------------F
//Back-------------------------B
//Left---------------------------L
//Right-------------------------R
//Forward Left--------------G
//Forward Right------------I
//Back Left------------------H
//Back Right----------------J
//Stop-------------------------S
//Front Lights On---------W
//Front Lights Off---------w (lower case)
//Back Lights On---------U
//Back Lights Off---------u (lower case)
//Speed 0-------------------0
//Speed 10-----------------1
//Speed 20-----------------2
//Speed 30-----------------3
//Speed 40-----------------4
//Speed 50-----------------5
//Speed 60-----------------6
//Speed 70-----------------7
//Speed 80-----------------8
//Speed 90-----------------9
//Speed 100---------------q

