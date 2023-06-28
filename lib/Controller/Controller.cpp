//
// Created by jeffr on 18-6-2023.
//

#include "Controller.h"
#include <sstream>
#include <utility>

void Controller::init(float maxSpeed) {
    SingletonPtr<Logger> singleton;
    _logger = singleton.get();
    MaxSpeed = maxSpeed;
    //_ticker.attach(callback(this, &Controller::updateLoop), _updateInterval);
    _logger->Log(INFO, "Controller: starting thread");
    //thread.start(callback(this, &Controller::updateLoop));
    //thread.set_priority(osPriorityLow);
    _logger->Log(INFO, "Controller:thread Started start");
}

[[noreturn]] void Controller::updateLoop() {
    while (true){
        _logger->Log(INFO, "Controller: updateLoop start");
        Update();
        _logger->Log(INFO, "Controller: updateLoop End");
        ThisThread::sleep_for(_updateInterval);
    }
}

Controller::Controller(std::shared_ptr<IDistance> FrontRight, std::shared_ptr<IDistance> FrontMiddle,
                       std::shared_ptr<IDistance> FrontLeft, std::shared_ptr<IDistance> DownRight,
                       std::shared_ptr<IDistance> DownMiddle, std::shared_ptr<IDistance> DownLeft,
                       std::shared_ptr<Mover> mover,  vector<std::shared_ptr<IMotor>> brushes) : _frontRight(std::move(FrontRight)), _frontMiddle(std::move(FrontMiddle)),
                       _frontLeft(std::move(FrontLeft)), _downRight(std::move(DownRight)), _downMiddle(std::move(DownMiddle)),
                       _downLeft(std::move(DownLeft)), _mover(std::move(mover)), turning(false),  _brushes(std::move(brushes)){
    SingletonPtr<Logger> singleton;
    _logger = singleton.get();
}

void Controller::Update() {
    SingletonPtr<Logger> singleton;
    _logger = singleton.get();
    _logger->Log(DEBUG, "Controller: Update");
    //todo check all sensor
    //if front sensors are less the frontDistance Turn
    if(_frontRight->GetDistanceMM() < _frontDistance || _frontMiddle->GetDistanceMM() < _frontDistance || _frontLeft->GetDistanceMM() < _frontDistance){
        _logger->Log(INFO, "Turning close to wall Ultrasoon");
        PrintSensors();
        Turn();
        return;
    }
    //if down sensors are more then DownDistance turn
    if (_downRight->GetDistanceMM() > _downDistance || _downMiddle->GetDistanceMM() > _downDistance || _downLeft->GetDistanceMM() > _downDistance)
    {

        _logger->Log(INFO, "Turning close to drop IR sensors");
        PrintSensors();
        Turn();
        return;
    }
    _logger->Log(DEBUG, "Moving Forward");
    SetSpeed(1);
    SetBrushes();
    _mover->SetMovement(Mover::Move::Forward);
}

void Controller::PrintSensors() {
    string a = "\n";
    a += (string)"frontRight: " + to_string(_frontRight->GetDistanceMM());
    a += (string)" DownRight: " + to_string(_downRight->GetDistanceMM()) + "\n";
    a += (string)"FrontMiddle: " + to_string(_frontMiddle->GetDistanceMM());
    a += (string)" DownMiddle: " + to_string(_downMiddle->GetDistanceMM()) + "\n";
    a += (string)"FrontLeft: " + to_string(_frontLeft->GetDistanceMM());
    a += (string)" DownLeft: " + to_string(_downLeft->GetDistanceMM()) + "\n";
    _logger->Log(INFO, (a.c_str()));
}

void Controller::SetSpeed(float speed) {
    SetBrushes();
    if (!enabled) {
        _mover->SetSpeed(0);
        return;
    }
    speed *= MaxSpeed;
    _mover->SetSpeed(max(speed, minSpeed));
    SetBrushes();

}

void Controller::Turn()
{
    turning = true;
    SetSpeed(0.2);
    _mover->SetMovement(Mover::Reverse);
    ThisThread::sleep_for(500ms);
    _mover->SetMovement(Mover::Move::TurnLeft);
    ThisThread::sleep_for(1s);
    turning = false;
}

void Controller::setActive(bool value) {
    enabled = value;
    SetBrushes();
    if (!enabled){//robot inactive
        SetSpeed(0);
    }
}

void Controller::SetBrushes() {
    bool state = (enabled && !turning);
    for (const std::shared_ptr<IMotor>& brush : _brushes) {
            brush->SetSpeed(state);
    }
}