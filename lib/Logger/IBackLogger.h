//
// Created by jeffr on 22-6-2023.
//

#ifndef SOFTWARE_IBACKLOGGER_H
#define SOFTWARE_IBACKLOGGER_H


#include <string>

class IBackLogger{
public:
    struct EventData {
        int type{};
        long long int time{};
        std::string message{};
    };
    virtual void Log(EventData eventData) = 0;
};

#endif //SOFTWARE_IBACKLOGGER_H
