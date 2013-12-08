/* 
 * File:   Serial.h
 * Author: bruno
 *
 * Created on November 15, 2013, 4:33 PM
 */

#ifndef SERIAL_H
#define	SERIAL_H

#include <string>

class Serial {
public:
    Serial();
    virtual ~Serial();
    int open_port(const char* serial_port);//returns 0 if fails
    int open_port(std::string serial_port);
    void close_port();
    const char* get_current_port();
    int write_on_port(const char* buffer);//returns 0 if fails
    int read_from_port(char* &buffer);
protected:
    int fd;//file descriptor
    const char* port;

};

#endif	/* SERIAL_H */

