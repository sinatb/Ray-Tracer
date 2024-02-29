//
// Created by sinat on 2/8/2024.
//

#ifndef HITTABLE_H
#define HITTABLE_H
class material;

class hit_record{
public:
    point3 hp;
    vec3 normal;
    shared_ptr<material> mat;
    double t;
    bool front_face;

    void set_face_normal(const ray& r,const vec3& outward_normal){
        front_face = dot(r.get_direction(),outward_normal) < 0.0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};
class hittable{
public:
    virtual ~hittable() = default;
    virtual bool hit (ray& r, interval ray_i, hit_record& h) const = 0;
};

#endif //HITTABLE_H
