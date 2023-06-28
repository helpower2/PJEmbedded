//
// Created by jeffr on 17-6-2023.
//

#ifndef SOFTWARE_ILOGGER_H
#define SOFTWARE_ILOGGER_H

#include "LogType.h"

class ILogger{
public:
    virtual void Log(Type type, const char* message) = 0;
};

#endif //SOFTWARE_ILOGGER_H
