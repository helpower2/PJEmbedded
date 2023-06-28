//
// Created by jeffr on 18-6-2023.
//

#ifndef SOFTWARE_CONTROLLER_H
#define SOFTWARE_CONTROLLER_H


#include <IDistance.h>
#include <memory>
#include <Mover.h>
#include <ILogger.h>
#include <Logger.h>

class Controller {
public:
    Controller(std::shared_ptr<IDistance> FrontRight,std::shared_ptr<IDistance> FrontMiddle,
               std::shared_ptr<IDistance> FrontLeft,std::shared_ptr<IDistance> DownRight,std::shared_ptr<IDistance> DownMiddle,
               std::shared_ptr<IDistance> DownLeft, std::shared_ptr<Mover> mover,  vector<std::shared_ptr<IMotor>> brushes);
    void init(float maxSpeed);
    void Update();
    void setActive(bool value);
    float MaxSpeed = 0.2;
    float minSpeed = 0.1;

private:
    std::shared_ptr<IDistance> _frontRight, _frontMiddle, _frontLeft, _downRight, _downMiddle, _downLeft;
    std::shared_ptr<Mover> _mover;
    Logger* _logger;
    chrono::duration<int64_t, milli> _updateInterval = 100ms;
    Thread thread;
    //Ticker _ticker;
    float _frontDistance = 100;
    float _downDistance = 500;
    void SetSpeed(float speed);
    void Turn();
    [[noreturn]] void updateLoop();
    bool enabled, turning;
    vector<std::shared_ptr<IMotor>> _brushes;
    void PrintSensors();
    void SetBrushes();
};


#endif //SOFTWARE_CONTROLLER_H
