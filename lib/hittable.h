//
// Created by sinat on 2/8/2024.
//

#ifndef HITTABLE_H
#define HITTABLE_H
#include "ray.h"
class hit_record{
public:
    point3 hp;
    vec3 normal;
    double t;
};
class hittable{
public:
    virtual ~hittable() = default;
    virtual bool hit (ray& r, double t_min, double t_max,hit_record& h) const = 0;
};
#endif //HITTABLE_H
