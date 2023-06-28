//
// Created by jeffr on 20-6-2023.
//

#ifndef SOFTWARE_HCSR04CONTROLLER_H
#define SOFTWARE_HCSR04CONTROLLER_H


#include <vector>
#include "HCSR04.h"

class HCSR04Controller {
public:
    HCSR04Controller();
    chrono::duration<int64_t, milli> interval = 60ms;
    void addSensor(HCSR04* sensor);
    void Init();

private:
    static vector<HCSR04*> SonicSensors;
    Thread runner;
    [[noreturn]] void SensorChecker() const;
};



#endif //SOFTWARE_HCSR04CONTROLLER_H
