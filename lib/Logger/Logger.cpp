//
// Created by jeffr on 14-6-2023.
//

#include "Logger.h"

#include <utility>


#define get_time_ms()     std::chrono::time_point_cast<std::chrono::milliseconds>(Kernel::Clock::now()).time_since_epoch().count()
std::vector<std::shared_ptr<IBackLogger>> Logger::Loggers;
int Logger::logLevel;

Logger::Logger(std::vector<std::shared_ptr<IBackLogger>> Loggers) {
    this->Loggers = std::move(Loggers);

}

void Logger::Log(Type type, const std::string &message) {
    Log(type, message.c_str());
}

void Logger::Log(Type type, const char *message) {

    if (core_util_is_isr_active()){
        events.call(Logs, type, message);
    }
    else{
        Logs(type, message);
    }

}

void Logger::Log(int type, const std::string &message) {
    Log(static_cast<Type>(type), message);
}

void Logger::Log(int type, const char *message) {
    Log(static_cast<Type>(type), message);
}


void Logger::addLogger(std::shared_ptr<IBackLogger> logger) {
    Loggers.push_back(logger);
    Logs(INFO, "Logger Added");
}

void Logger::SendToLoggers(const IBackLogger::EventData& eventData) {
    for (auto & Logger : Loggers) {
        Logger->Log(eventData);
    }
}

void Logger::HandleTread() {
    //thread.start(callback(&events, &EventQueue::dispatch_forever));
    //thread.set_priority(osPriorityHigh);
}

Logger::Logger() : events(32 * 400)
{}

void Logger::Logs(Type type, const char *message) {
    if ((int) type < logLevel)
        return;
    IBackLogger::EventData event {type, get_time_ms(), message};
    SendToLoggers(event);
}

void Logger::QueuLog(Type type, const string &message) {
    events.event(Logs, type, message.c_str());
}

u_int Logger::LoggerCount() {
    return Loggers.size();
};



