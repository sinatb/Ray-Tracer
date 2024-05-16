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
    interval(const interval& a, const interval& b) {
        min = a.min <= b.min ? a.min : b.min;
        max = a.max >= b.max ? a.max : b.max;
    }
    double size() const {
        return max - min;
    }
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
    interval expand(double delta) const {
        auto padding = delta/2;
        return interval(min - padding, max + padding);
    }
    static const interval empty, universe;
};

const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

interval operator+(const interval& ival, double displacement) {
    return interval(ival.min + displacement, ival.max + displacement);
}

interval operator+(double displacement, const interval& ival) {
    return ival + displacement;
}
#endif //INTERVAL_H
