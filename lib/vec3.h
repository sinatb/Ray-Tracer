//
// Created by sinat on 2/3/2024.
//

#ifndef VEC3_H
#define VEC3_H

#endif //VEC3_H

#include "iostream"
#include "cmath"

using std::sqrt;

class vec3{
    public:
        double e[3];

        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0,e1,e2} {}

        [[nodiscard]] double x() const {return e[0];}
        [[nodiscard]] double y() const {return e[1];}
        [[nodiscard]] double z() const {return e[2];}

        vec3 operator-() const {return {-e[0],-e[1],e[2]};}
        double operator[] (int i) const {return e[i];}
        double& operator[] (int i) {return e[i];}

        vec3& operator+= (const vec3 &v){
            e[0] += v.x();
            e[1] += v.y();
            e[2] += v.z();
            return *this;
        }

        vec3& operator-= (const vec3 &v){
            e[0] -= v.x();
            e[1] -= v.y();
            e[2] -= v.z();
            return *this;
        }

        vec3 operator*= (const double t){
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3 operator/= (const double t){
            return *this *= 1/t;
        }

        double length_squared(){
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double length(){
            return sqrt(length_squared());
        }
};


