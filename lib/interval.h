//
// Created by sinat on 2/16/2024.
//

#ifndef INTERVAL_H
#define INTERVAL_H
#include <limits>

class interval{
public:
    double min,max;
    interval() : min(std::numeric_limits<double>::infinity()) ,
                 max(-std::numeric_limits<double>::infinity())
                 {};

    interval(double min, double max) : min(min),
                                       max(max)
                                       {};

    bool contains(double a) const{
        return a >= min && a <= max;
    }

    bool surrounds(double a) const{
        return a > min && a < max;
    }

    static const interval empty, universe;
};

const static interval empty();
const static interval universe(-std::numeric_limits<double>::infinity(),std::numeric_limits<double>::infinity());

#endif //INTERVAL_H
