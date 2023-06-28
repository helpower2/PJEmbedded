#ifndef LOGGER_H
#define LOGGER_H

#include "mbed.h"
#include "string"
#include <SingletonPtr.h>
#include <Logger.h>
#include <ILogger.h>
#include <IBackLogger.h>
#include "LogType.h"

class SerialLogger : public IBackLogger{
private:
    //Timer time;
    //EventQueue _queue;
    //Thread thread;
    void Log(EventData eventData) override;

public:
    SerialLogger();//make sure to call before calling Log
};

#endif /* LOGGER_H */
