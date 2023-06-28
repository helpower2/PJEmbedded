#include <sstream>
#include "SerialLogger.h"

#define MAXIMUM_BUFFER_SIZE 1024

static BufferedSerial serial_port(USBTX, USBRX, 115200);//9600 19200 115200
//static BufferedSerial serial_port(USBTX, USBRX, 19200 );

FileHandle *mbed::mbed_override_console(int fd)
{
    return &serial_port;
}

SerialLogger::SerialLogger()// : _queue(64 * sizeof(SerialLogger::EventData)), thread(osPriorityBelowNormal)
{
    DigitalOut led(LED1);
    led.write(0);
    if(serial_port.writable()){
        led.write(1);
    }

    //time.start();
    //thread.start(callback(&_queue, &EventQueue::dispatch_forever));
}

void SerialLogger::Log(EventData eventData)
{
    LogType type = LogType(eventData.type);
    auto s =to_string(eventData.time) + ": Event " +
            type.tostring() + " " + eventData.message + "\n";
    auto c = s.c_str();
    //printf("%s", c);
    serial_port.write(c, s.length());
    //serial_port.write("%lld Event %s: %s\n", eventData.time, type.tostring().c_str(),
    // eventData.message.c_str());
}



