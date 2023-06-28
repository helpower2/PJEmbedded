//
// Created by jeffr on 8-5-2023.
//

#ifndef VERKEERSLICHT_LOGTYPE_H
#define VERKEERSLICHT_LOGTYPE_H

#include <string>
#include <TypeBase.h>
enum Type{
    DEBUG,
    INFO,
    WARNING,
    CRITICAL,
    FATAL,
};

class LogType : TypeBase<Type> {
public:
    explicit LogType(int i) : TypeBase(i) {}
    explicit LogType(Type i) : TypeBase(i) {}
    std::string tostring() override {
        switch (value_) {
            case DEBUG: return "DEBUG";
            case INFO:return "INFO";
            case WARNING:return "WARNING";
            case CRITICAL:return "CRITICAL";
            case FATAL:return "FATAL";
        }
        return "NULL";
    }
};


#endif //VERKEERSLICHT_LOGTYPE_H
