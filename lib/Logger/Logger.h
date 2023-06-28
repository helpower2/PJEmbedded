//
// Created by jeffr on 14-6-2023.
//

#ifndef SOFTWARE_LOGGER_H
#define SOFTWARE_LOGGER_H

#include <memory>
#include <queue>
#include "mbed.h"
#include "LogType.h"
#include "string"
#include "ILogger.h"
#include "IBackLogger.h"

class Logger : public ILogger {
public:
    //static std::shared_ptr<ILogger> Instance;
    explicit Logger( std::vector<std::shared_ptr<IBackLogger>> Loggers);
    Logger();
    void Log(int type, const char* message);
    void Log(int type, const std::string& message);
    void Log(Type type, const char* message) override;

    void Log(Type type, const std::string& message);
    void QueuLog(Type type, const std::string& message);
    EventQueue events;
    //void addLogger(ILogger* logger);
    void addLogger(std::shared_ptr<IBackLogger> logger);
    static u_int LoggerCount();
    static int logLevel;
private:
    static void Logs(Type type, const char* message);
    static void SendToLoggers(const IBackLogger::EventData& eventData);
    void HandleTread();
    static std::vector<std::shared_ptr<IBackLogger>> Loggers;

    Thread thread;
};


#endif //SOFTWARE_LOGGER_H
