//
// Created by jeffr on 24-6-2023.
//

#ifndef SOFTWARE_L298N_DRIVER_H
#define SOFTWARE_L298N_DRIVER_H


#include <Motor-Base/IMotor.h>
#include <mbed.h>

class L298N_Driver : public IMotor{
public:
    void SetSpeed(float speed) override;

    float GetSpeed() override;
    Direction GetDirection() override;

    //L298N_PWM_Driver(PinName in1,PinName in2);
    L298N_Driver(PinName in1, PinName in2);

    void SetDirection(Direction direction) override;

private:
    DigitalOut forward, backwards;
    void SetOutputs();
};


#endif //SOFTWARE_L298N_DRIVER_H
