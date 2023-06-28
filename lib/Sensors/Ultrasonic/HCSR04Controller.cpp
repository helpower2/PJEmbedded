//
// Created by jeffr on 20-6-2023.
//

#include "HCSR04Controller.h"

std::vector<HCSR04*> HCSR04Controller::SonicSensors;

void HCSR04Controller::addSensor(HCSR04* sensor) {
    HCSR04Controller::SonicSensors.push_back(sensor);
}

void HCSR04Controller::Init() {

    runner.start(callback(this, &HCSR04Controller::SensorChecker));
}

[[noreturn]] void HCSR04Controller::SensorChecker() const {
    while(true){
        for (const auto& sensor : HCSR04Controller::SonicSensors) {
            sensor->measureDistance();
            ThisThread::sleep_for(interval);
//            if (sensor->Ismesuring()){
//                printf("Sensor failed  \n");
//                sensor->SetFailed();
//            }
        }
    }
}

HCSR04Controller::HCSR04Controller() {}
