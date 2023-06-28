//
// Created by jeffr on 14-6-2023.
//

#ifndef SOFTWARE_IDISTANCE_H
#define SOFTWARE_IDISTANCE_H


class IDistance {
public:
    virtual double GetDistanceMM() =0;
    virtual double GetDistanceCM() =0;
};


#endif //SOFTWARE_IDISTANCE_H
