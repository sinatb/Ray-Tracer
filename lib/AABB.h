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
        for (int a = 0; a < 3; a++) {
            auto invD = 1.0f / r.get_direction()[a];
            auto t0 = (minimum[a] - r.get_start()[a]) * invD;
            auto t1 = (maximum[a] - r.get_start()[a]) * invD;
            if (invD < 0.0f)
                std::swap(t0, t1);
            t_min = t0 > t_min ? t0 : t_min;
            t_max = t1 < t_max ? t1 : t_max;
            if (t_max <= t_min)
                return false;
        }
        return true;
    }
};
#endif //RAY_TRACER_AABB_H
