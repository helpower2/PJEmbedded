/* mbed SHARPIR distance sensor
 * Copyright (c) 2010 Tomas Johansen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "mbed.h"
#include "SHARPIR.h"

SHARPIR::SHARPIR(PinName AnalogPort)
        : analogIn(AnalogPort) {

}

double SHARPIR::volt() {
    return(analogIn.read() * 3.3); //analogin function returns a percentage which describes how much of 3.3v it's reading, therefor multiply it by 3,3 to get the correct analogin voltage.
}

double SHARPIR::GetDistanceCM() {
    double v = volt();
    if (v > higherRange) //sensor is out of higher range
        return(999999);
    else if (v < lowerRange)
        return(999999); //sensor is out of lower range
    else
        return 2;
        return(reg*pow(v, exp));
}

double SHARPIR::GetDistanceMM() {
    return GetDistanceCM()*10;
}
