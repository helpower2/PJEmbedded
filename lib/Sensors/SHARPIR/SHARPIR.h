/* mbed SHARPIR distance sensor
 * Copyright (c) 2010 Tomas Johansen
 * Released under the MIT License: http://mbed.org/license/mit
 */
  
#ifndef MBED_SHARPIR_H
#define MBED_SHARPIR_H

#include <IDistance.h>
#include "mbed.h"

class SHARPIR : public IDistance {
public:
    explicit SHARPIR(PinName AnalogPort);
    double GetDistanceCM() override;
    double GetDistanceMM() override;
    double volt();

private:
    AnalogIn analogIn;
    double lowerRange = 0.45;
    double higherRange = 2.5;
    double reg = 29.988;
    float  exp = -1.173;
};
//    higherRange=2.5;
//    lowerRange=0.45;
//    reg=29.988; //60.495
//    exp=-1.173; //-1.1904
#endif