//
// Created by sinat on 2/10/2024.
//

#ifndef COMMONS_H
#define COMMONS_H
#include <cmath>
#include <limits>
#include "cstdlib"
#include <memory>
#include "interval.h"

// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}
inline double rnd_double(){
    return rand() / (RAND_MAX+1.0);
}
inline double rnd_double_rng(double min, double max){
    return min + rnd_double()*(max-min);
}

// Common Headers
#include "ray.h"
#include "vec3.h"



#endif //COMMONS_H
