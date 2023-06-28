//
// Created by jeffr on 24-6-2023.
//

#include "L298N_Driver.h"

L298N_Driver::L298N_Driver(PinName in1, PinName in2): forward(in1), backwards(in2) {
    forward.write(0);
    backwards.write(0);
}

void L298N_Driver::SetDirection(IMotor::Direction direction) {
    _direction = direction;
    SetOutputs();
}

void L298N_Driver::SetSpeed(float speed) {
    if(speed > 0.5) _speed = 1;
    else _speed = 0;
    SetOutputs();
}

IMotor::Direction L298N_Driver::GetDirection() {
    return _direction;
}

float L298N_Driver::GetSpeed() {
    return _speed;
}

void L298N_Driver::SetOutputs() {
    switch (_direction) {
        case Forward:
            backwards.write(0);
            forward.write((int)_speed);
            break;
        case Reverse:
            forward.write(0);
            backwards.write((int)_speed);
            break;
    }
}
