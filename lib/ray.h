//
// Created by sinat on 2/4/2024.
//

#ifndef RAY_H
#define RAY_H
#include "vec3.h"
class ray{
public:
    ray()= default ;

    ray(const point3& start,const vec3& direction) : direction(direction), start(start){}

    point3 get_start() const{
        return start;
    }
    vec3 get_direction() const{
        return direction;
    }

    [[nodiscard]] point3 at (double t) const{
        return start + direction*t;
    }


private:
    point3 start;
    vec3 direction;
};
#endif //RAY_H
