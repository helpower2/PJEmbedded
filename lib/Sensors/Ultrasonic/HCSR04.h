//
// Created by jeffr on 24-5-2023.
//
#ifndef SOFTWARE_HCSR04_H
#define SOFTWARE_HCSR04_H

#include <IDistance.h>

#include <utility>
#include <Logger.h>
#include "mbed.h"

class HCSR04 : public IDistance{
public:
    HCSR04(PinName triggerPin, PinName echoPin) :
    trigger(triggerPin), echo(echoPin), logger(singleton.get()) {
        echo.rise(callback(this, &HCSR04::handleEchoRise));
        echo.fall(callback(this, &HCSR04::handleEchoFall));
        echo.mode(PinMode::PullDown);
        pulseWidth = 0.0;
        distance = -1;
        events = &logger->events;
    }

    double GetDistanceCM() override  {
        if(distance == -1)
            return 9000;
            //ThisThread::sleep_for(100ms);
        return distance / 58;
    }

    double GetDistanceMM() override {
        if(distance == -1)
            return 9000;
        return (distance ) * 10;
    };

    void measureDistance() {
        if (mesuring){
            distance = -1;
        }
//        if(logger->events.call(Logger::Logs, DEBUG, "start") ==0)//event not created
//            printf("not logging");
        trigger = 1;                    // Send a 10us pulse to start ranging
        wait_us(50);
        trigger = 0;
        mesuring = true;
    }
//    void SetDistance(double dist){
//        distance = dist;
//    }
    bool Ismesuring(){
        return mesuring;
    }
    void SetFailed(){
        mesuring = false;
    }

private:
    static Timer echoTimer;
    DigitalOut trigger;
    InterruptIn echo;
    double pulseWidth;
    double distance = -1;
    bool mesuring = false;
    SingletonPtr<Logger> singleton;
    Logger* logger;
    EventQueue* events;
    void handleEchoRise() {
        //logger->events.call(Logger::Logs, DEBUG, "Echo start recieved");
            echoTimer.reset();
            echoTimer.start();              // Start the timer
        };

    void handleEchoFall() {
        //logger->events.call(Logger::Logs, DEBUG, "Echo start recieved");
        echoTimer.stop();// Stop the timer
        pulseWidth = echoTimer.elapsed_time().count();  // Get pulse width in microseconds
        if(pulseWidth != 0)
            distance = pulseWidth / 58;    // Calculate distance in centimeters (velocity of sound in air is ~ 340 m/s)
        echoTimer.reset();
        mesuring = false;
        //logger->QueuLog(DEBUG, to_string(distance) + "\n");//mag niet in ISR context
    }
};




#endif // SOFTWARE_HCSR04_H
