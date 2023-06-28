//
// Created by jeffr on 26-5-2023.
//

#ifndef SOFTWARE_IMOTOR_H
#define SOFTWARE_IMOTOR_H

class IMotor {
public:
    enum Direction
    {
        Forward = 0,
        Reverse = 1,
    };

    virtual void SetDirection(Direction direction) = 0;
    virtual void SetSpeed(float speed) = 0;

    virtual float GetSpeed() =0;
    virtual Direction GetDirection() = 0;

protected:
    Direction _direction = Forward;
    float _speed = 0;
};


#endif //SOFTWARE_IMOTOR_H
