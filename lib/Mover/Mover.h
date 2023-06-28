//
// Created by jeffr on 12-6-2023.
//

#ifndef SOFTWARE_MOVER_H
#define SOFTWARE_MOVER_H


#include <Motor-Base/IMotor.h>
#include <mbed.h>


class Mover {
public:
    enum Move {
        Forward,
        Reverse,
        TurnLeft,
        TurnRight
    };

    void SetSpeed(float speed);
    void SetMovement(Move move);
    void SetState(bool active);
    //Mover(IMotor& Left,IMotor& Right);
    Mover(std::shared_ptr<IMotor> left, std::shared_ptr<IMotor> right);
    //Mover(PinName left1, PinName left2, PinName right1, PinName right2);
private:
    //chrono::duration<int64_t, milli> turnTime = 300ms;
    Move _move, _nextMove;
    std::shared_ptr<IMotor> leftWheel, rightWheel;
    //IMotor &leftWheel, &rightWheel;
    bool _turning = false;
//    bool _active = false;
    void Move();
};
//todo take in to acount battery

#endif //SOFTWARE_MOVER_H
