
#include "Serial.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include <sys/types.h>//needed to use the ssize_t

Serial::Serial()
{
    port = "";
    fd = -1;
}

Serial::~Serial() 
{
    close_port();
}

int Serial::open_port(const char* serial_port)
{
    close_port();//closes the last port opened
    fd = open(serial_port, O_WRONLY);
    if (fd == -1)
    {
        port = NULL;
        return 0;        
    }
    port = serial_port;
    return 1;
}

int Serial::open_port(std::string serial_port)
{
    close_port();//closes the last port opened
//    std::ostringstream strstream;
    const char* portBuffer = serial_port.c_str();
    fd = open(portBuffer, O_WRONLY);
    if (fd == -1)
    {
        port = NULL;
        return 0;
    }
    port = portBuffer;
    return 1;
}

void Serial::close_port()
{
    close(fd);
    fd = -1;
}

int Serial::write_on_port(const char* buffer)
{
    if(fd != -1)
    {
        write(fd, buffer, strlen(buffer));
        return 1;
    }  
    return 0;
}

const char* Serial::get_current_port()
{
    
    return port;
}

int Serial::read_from_port(char* & buffer)
{
    bool success = true;
    if(fd != -1)
    {
        using namespace std;
        while(1)
            {
                char buff[100];
                ssize_t length = read(fd, &buff, sizeof(buff));
                if (length == -1)
                {
//                    cout << "Error reading from serial port\n" << endl;
                    success = false;
                    break;
                }
                else if (length == 0)
                {
                    cout << "No more data\n" << endl;
                    break;
                }
                else
                {
                    buff[length] = '\0';
//                    cout << "buff = " << buff << endl;
                    buffer = buff;
                }
             }
        if(success)
         return 1;
    }
    return 0;
}
