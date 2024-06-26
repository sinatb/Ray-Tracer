//
// Created by sinat on 2/3/2024.
//

#ifndef VEC3_H
#define VEC3_H

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
        [[nodiscard]] bool near_zero() const {
            auto s = 1e-8;
            return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
        }

        static vec3 random_vector(double min, double max){
            return {random_double(min,max),random_double(min,max),random_double(min,max)};
        }
};
using point3 = vec3;

inline vec3 operator+ (const vec3& a, const vec3& b){
    return {a.x() + b.x(), a.y() + b.y() , a.z() + b.z()};
}
inline vec3 operator- (const vec3& a, const vec3& b){
    return {a.x()-b.x(), a.y()-b.y(), a.z()-b.z()};
}
inline vec3 operator* (const vec3& a, const vec3& b){
    return {a.x()*b.x(), a.y()*b.y(), a.z()*b.z()};
}
inline vec3 operator* (const double t, const vec3& b){
    return {t*b.x(), t*b.y(), t*b.z()};
}
inline vec3 operator* (const vec3& a, const double t){
    return t*a;
}
inline vec3 operator/ (const vec3& a, const double t){
    return {a.x()/t, a.y()/t, a.z()/t};
}
inline std::ostream& operator<<(std::ostream &out, vec3& a){
    return out << a.x() << " " << a.y() << " " << a.z();
}
inline double dot(const vec3& a, const vec3& b){
    return a.x()*b.x() +
           a.y()*b.y() +
           a.z()*b.z();
}
inline vec3 cross(vec3& a, vec3& b){
    return {a.y() * b.z() - a.z() * b.y(),
            a.z() * b.x() - a.x() * b.z(),
            a.x() * b.y() - a.y() * b.x()};
}
inline vec3 unit_vector(vec3 a){
    return a/a.length();
}
inline vec3 random_in_unit_sphere(){
    while (true){
        auto v = vec3::random_vector(-1,1);
        if (v.length_squared() < 1)
            return v;
    }
}
inline vec3 random_unit_vector(){
    return unit_vector(random_in_unit_sphere());
}
inline vec3 random_on_hemisphere(const vec3& normal){
    auto v = random_unit_vector();
    if (dot(normal,v) > 0)
        return v;
    else
        return -v;
}
vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}
inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}
#endif //VEC3_H

