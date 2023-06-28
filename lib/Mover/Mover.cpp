//
// Created by jeffr on 12-6-2023.
//

#include <Motor-Base/IMotor.h>

#include <utility>
#include <Logger.h>
#include "Mover.h"

//Mover::Mover(IMotor& Left, IMotor& Right) : _move(Forward), _nextMove(Forward), leftWheel((IMotor &) left), rightWheel((IMotor &) right){}

void Mover::Move() {
    SingletonPtr<Logger> singleton;
    auto _logger = singleton.get();
    //can't wait here it stops checking then
    switch (_move) {
        case Forward:
            _logger->Log(DEBUG, "Mover Forward");
            leftWheel->SetDirection((IMotor::Direction::Forward));
            rightWheel->SetDirection((IMotor::Direction::Forward));
            break;
        case Reverse:
            _logger->Log(DEBUG, "Mover Reverse");
            leftWheel->SetDirection((IMotor::Direction::Reverse));
            rightWheel->SetDirection((IMotor::Direction::Reverse));
            break;
        case TurnLeft:
            _logger->Log(DEBUG, "Mover turnLeft");
            _turning = true;
            leftWheel->SetDirection(IMotor::Forward);
            rightWheel->SetDirection(IMotor::Reverse);
            _logger->Log(DEBUG, "Mover: Direction Set");
            //ThisThread::sleep_for(turnTime);
            _logger->Log(DEBUG, "Mover Sleep done");
            _turning = false;

            _nextMove = Forward;
            _logger->Log(DEBUG, "Mover NextMove Set");
            break;
        case TurnRight:
            _logger->Log(DEBUG, "Mover turnRight");
            _turning = true;
            leftWheel->SetDirection(IMotor::Reverse);
            rightWheel->SetDirection(IMotor::Forward);
            //ThisThread::sleep_for(turnTime);
            _turning = false;
            //_nextMove = Forward;
    }
    _logger->Log(DEBUG, "Mover _move set");
}

void Mover::SetMovement( enum Move move) {
//    if (_turning)
//    switch (move) {
//        case Forward:
//        case Reverse:
//            _nextMove = move;
//            break;
//        case TurnLeft:
//        case TurnRight:
//            _nextMove = Move::Forward;
//            break;
//    }
//    else
    {
        _move =move;
    }
    Move();
}

void Mover::SetSpeed(float speed) {
    rightWheel->SetSpeed(speed);
    leftWheel->SetSpeed(speed);
}

Mover::Mover(std::shared_ptr<IMotor> left, std::shared_ptr<IMotor> right) : _move(Forward), _nextMove(Forward), leftWheel(std::move(left)), rightWheel(std::move(right)){
}

//void Mover::SetState(bool active) {
//    _active = active;
//}
