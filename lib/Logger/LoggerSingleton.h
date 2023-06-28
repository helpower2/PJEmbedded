//
// Created by jeffr on 22-6-2023.
//

#ifndef SOFTWARE_LOGGERSINGLETON_H
#define SOFTWARE_LOGGERSINGLETON_H

#include "Logger.h"
#include "SingletonPtr.h"

class LoggerSingleton{
    static SingletonPtr<Logger> singleton;
};
#endif //SOFTWARE_LOGGERSINGLETON_H
