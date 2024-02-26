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

    [[nodiscard]] bool contains(double a) const{
        return a >= min && a <= max;
    }

    [[nodiscard]] bool surrounds(double a) const{
        return a > min && a < max;
    }

    [[nodiscard]] double clamp(double a) const{
        if (a > max) return max;
        if (a < min) return min;
        return a;
    }

    static const interval empty, universe;
};

const static interval empty();
const static interval universe(-std::numeric_limits<double>::infinity(),std::numeric_limits<double>::infinity());

#endif //INTERVAL_H
