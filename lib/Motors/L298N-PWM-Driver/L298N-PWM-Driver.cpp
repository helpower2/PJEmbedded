//
// Created by jeffr on 26-5-2023.
//

#include "L298N-PWM-Driver.h"

L298N_PWM_Driver::L298N_PWM_Driver(PinName in1, PinName in2, PinName EnablePWM) : forward(in1), backwards(in2), enable(EnablePWM) {
    enable.period_ms(periodMs);
    forward.write(0);
    backwards.write(0);
}


void L298N_PWM_Driver::SetDirection(IMotor::Direction direction) {
    _direction = direction;
    SetOutputs();
}

void L298N_PWM_Driver::SetSpeed(float speed) {
    _speed = speed;
    SetOutputs();
}

float L298N_PWM_Driver::GetSpeed() {
    return _speed;
}

IMotor::Direction L298N_PWM_Driver::GetDirection() {
    return _direction;
}

void L298N_PWM_Driver::SetOutputs() {
    enable.write(_speed);
    switch (_direction) {
        case Forward:
            backwards.write(0);
            forward.write(1);
            break;
        case Reverse:
            forward.write(0);
            backwards.write(1);
            break;
    }
}

