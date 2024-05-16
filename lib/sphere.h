//
// Created by sinat on 2/8/2024.
//

#ifndef SPHERE_H
#define SPHERE_H
#include <utility>
#include "commons.h"
#include "hittable.h"
#include "ray.h"
class sphere : public hittable{
public:
    //Beware this std::move might create problems;
    sphere(point3 center, double radius, shared_ptr<material> m) : center(center), radius(radius), mat(std::move(m))
    {
        auto rvec = vec3(radius, radius, radius);
        bbox = aabb(center - rvec, center + rvec);
    }
    bool hit(ray &r, interval ray_i, hit_record &h) const override {
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

        if (!ray_i.surrounds(r1)){
            root = r2;
            if (!ray_i.surrounds(r2))
                return false;
        }

        h.t = root;
        h.hp = r.at(root);
        auto normal = (h.hp - center)/radius;
        h.set_face_normal(r,normal);
        h.mat = mat;

        return true;
    }
    aabb bounding_box() const override{
        return bbox;
    }
private:
    vec3 center;
    aabb bbox;
    shared_ptr<material> mat;
    double radius;
};
#endif //SPHERE_H
