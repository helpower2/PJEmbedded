#include <mbed.h>
#include "SingletonPtr.h"
#include <Logger.h>
#include <SerialLogger.h>
#include "DebouncedButton.h"
#include <HCSR04.h>
#include <SHARPIR.h>
#include <Mover.h>
#include <Motor-Base/IMotor.h>
#include <HCSR04Controller.h>
#include <L298N-Driver/L298N_Driver.h>
#include <L298N-PWM-Driver/L298N-PWM-Driver.h>
#include "Controller.h"
//#include <oled_ssd1351.h>

#define buzzer D12

//infra rood
#define Ir_R A0
#define Ir_M A1
#define Ir_L A2
#define Ir_FM A3

//ultrasoon pins
#define trig_R D5
#define echo_R D4
#define trig_L D7
#define echo_L D6
#define trig_M D2
#define echo_M D3

//motors
#define MainIn1 D8
#define MainIn2 D9
#define MainIn3 D10
#define MainIn4 D11
#define MainEnable1 PC_6
#define MainEnable2 PC_8
#define SecIn1 PB_12
#define SecIn2 PA_11
#define SecIn3 PB_2
#define SecIn4 PB_1

std::shared_ptr<IBackLogger> serialLogger(new SerialLogger());
SingletonPtr<Logger> singleton;
//oled::SSD1351 Oled(D4, D3, D15, D5, D7, D14);


//L298N_PWM_Driver brushLeft(SecIn1, SecIn2);
//L298N_PWM_Driver brushRight(SecIn3, SecIn4);

//std::shared_ptr<IDistance> Front = {new SHARPIR(Ir_R), }



std::shared_ptr<IDistance> DownRight(new SHARPIR(Ir_R));
std::shared_ptr<IDistance> DownMiddle(new SHARPIR(Ir_M));
std::shared_ptr<IDistance> DownLeft(new SHARPIR(Ir_L));

std::shared_ptr<HCSR04Controller> hcsr04Controller(new HCSR04Controller());

HCSR04 *frontRight(new  HCSR04(trig_R, echo_R));
HCSR04 *frontLeft(new HCSR04(trig_L, echo_L));
HCSR04 *frontMiddle(new HCSR04(trig_M, echo_M));


//std::shared_ptr<IDistance> FrontMiddle(new SHARPIR(Ir_FM));
std::shared_ptr<IDistance> FrontMiddle(frontMiddle);
std::shared_ptr<IDistance> FrontLeft(frontLeft);
std::shared_ptr<IDistance> FrontRight(frontRight);

std::shared_ptr<IMotor> leftWheel(new L298N_PWM_Driver(MainIn1, MainIn2, MainEnable1));
std::shared_ptr<IMotor> rightWheel(new L298N_PWM_Driver(MainIn3, MainIn4, MainEnable2));

std::shared_ptr<IMotor> leftBroom(new L298N_Driver(SecIn1, SecIn2));
std::shared_ptr<IMotor> rightBroom(new L298N_Driver(SecIn3, SecIn4));

std::shared_ptr<Mover> mover(new Mover(leftWheel, rightWheel));

Controller controller(FrontRight, FrontMiddle, FrontLeft, DownRight, DownMiddle, DownLeft, mover, {leftBroom, rightBroom});

void PrintSensors();

void TestMover();
void ToggleActive();

void SetSpeed(){
    mover->SetMovement(Mover::Forward);
    mover->SetSpeed(1);
}

bool active = false;

DebouncedButton button(USER_BUTTON, ToggleActive, PinMode::PullUp, 100ms, *new Timer);

int main() {
    //printf ("started main function");
    Logger* logger = (singleton.get());
    logger->logLevel = 1;
    logger->addLogger(serialLogger);
    logger->Log(Type::DEBUG, "Logger: Started");
    hcsr04Controller->addSensor(frontRight);
    hcsr04Controller->addSensor(frontLeft);
    hcsr04Controller->addSensor(frontMiddle);
    hcsr04Controller->Init();
    logger->Log(Type::INFO, "hcsr04Controller: Started");
    controller.init(1);
    logger->Log(Type::INFO, "controller: Started");
    //controller.MaxSpeed = 1;
    while(1) {
        //PrintSensors();
        controller.setActive(active);
        controller.Update();
        ThisThread::sleep_for(50ms);//KEEP here for logger to work

    }
}

void TestMover() {
    mover->SetSpeed(1);
    mover->SetMovement(Mover::Forward);
    ThisThread::sleep_for(1s);//KEEP here for logger to work
    mover->SetSpeed(1);
    mover->SetMovement(Mover::Reverse);
    ThisThread::sleep_for(1s);//KEEP here for logger to work
    mover->SetSpeed(1);
    mover->SetMovement(Mover::TurnLeft);
    ThisThread::sleep_for(1s);//KEEP here for logger to work
    mover->SetSpeed(1);
    mover->SetMovement(Mover::TurnRight);
    ThisThread::sleep_for(1s);//KEEP here for logger to work

}


void PrintSensors() {
    Logger* logger = (singleton.get());
    string a = "\n";
    a += (string)"frontRight: " + to_string(FrontRight->GetDistanceMM());
    a += (string)" DownRight: " + to_string(DownRight->GetDistanceMM()) + "\n";
    a += (string)"FrontMiddle: " + to_string(FrontMiddle->GetDistanceMM());
    a += (string)" DownMiddle: " + to_string(DownMiddle->GetDistanceMM()) + "\n";
    a += (string)"FrontLeft: " + to_string(FrontLeft->GetDistanceMM());
    a += (string)" DownLeft: " + to_string(DownLeft->GetDistanceMM()) + "\n";
    logger->Log(INFO, (a.c_str()));
}

void ToggleActive(){
    active = !active;
}