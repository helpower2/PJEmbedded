//
// Created by jeffr on 26-5-2023.
//

#ifndef SOFTWARE_L298N_PWM_DRIVER_H
#define SOFTWARE_L298N_PWM_DRIVER_H


#include <Motor-Base/IMotor.h>
#include <mbed.h>
//#include <PinNames.h>

class L298N_PWM_Driver : public IMotor {
public:
    void SetSpeed(float speed) override;

    float GetSpeed() override;
    Direction GetDirection() override;

    //L298N_PWM_Driver(PinName in1,PinName in2);
    L298N_PWM_Driver(PinName in1, PinName in2, PinName EnablePWM);

    void SetDirection(Direction direction) override;

private:
    DigitalOut forward, backwards;
    PwmOut enable;
    void SetOutputs();
    int periodMs = 25;
};

#endif //SOFTWARE_L298N_PWM_DRIVER_H
