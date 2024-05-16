//
// Created by sinat on 5/16/2024.
//

#ifndef RAY_TRACER_AABB_H
#define RAY_TRACER_AABB_H
#include "commons.h"
class aabb{

public:
    point3 minimum;
    point3 maximum;
    aabb(){}
    aabb(const point3& minimum_p, const point3& maximum_p) : minimum(minimum_p),maximum(maximum_p){}

    bool hit(const ray& r,double t_min, double t_max)
    {
        for (int c=0;c<3;c++){
            auto t0 = fmin((minimum[c] - r.get_start()[c]) / r.get_direction()[c],
                           (maximum[c] - r.get_start()[c]) / r.get_direction()[c]);
            auto t1 = fmax((minimum[c] - r.get_start()[c]) / r.get_direction()[c],
                           (maximum[c] - r.get_start()[c]) / r.get_direction()[c]);
            t_min = fmax(t0, t_min);
            t_max = fmin(t1, t_max);
            if (t_max <= t_min)
                return false;
        }
        return true;
    }
};
#endif //RAY_TRACER_AABB_H
