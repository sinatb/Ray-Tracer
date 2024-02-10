//
// Created by sinat on 2/8/2024.
//

#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.h"
#include "ray.h"
class sphere : public hittable{
public:
    sphere(point3 center, double radius) : center(center), radius(radius){}
    bool hit(ray &r, double t_min, double t_max, hit_record &h) const override {
        auto oc = r.get_start() - center;
        auto a = dot(r.get_direction(),r.get_direction());
        auto b = 2*dot(r.get_direction(),oc);
        auto c = dot(oc,oc) - radius*radius;
        auto delta = b*b-4*a*c;

        if (delta < 0.0)
            return false;

        auto r1 = (-b - sqrt(delta))/2*a;
        auto r2 = (-b + sqrt(delta))/2*a;
        auto root = r1;

        if (r1 > t_max || r1 < t_min){
            root = r2;
            if (r2 > t_max || r2 < t_min)
                return false;
        }

        h.t = root;
        h.hp = r.at(root);
        auto normal = (h.hp - center)/radius;
        h.set_face_normal(r,normal);

        return true;
    }
private:
    vec3 center;
    double radius;
};
#endif //SPHERE_H
