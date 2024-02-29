//
// Created by sinat on 2/28/2024.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "commons.h"

#include "hittable.h"


class material{

public:
    virtual ~material() = default;

    virtual bool scatter(const ray& r_in,const hit_record& h, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material{
public:
    lambertian(const color& a) : albedo(a){}

    bool scatter(const ray& r_in,const hit_record& h, color& attenuation, ray& scattered)
    const override{
        auto dir = unit_vector(h.hp + random_unit_vector());
        if (dir.near_zero()){
            dir = h.hp;
        }
        scattered = ray(h.hp, dir);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

class metal : public material{
public:
    metal(const color& a) : albedo(a) {}

    bool scatter(const ray& r_in, const hit_record& h, color& attenuation, ray& scattered)
    const override {
        vec3 reflected = reflect(unit_vector(r_in.get_direction()), h.normal);
        scattered = ray(h.hp, reflected);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};
#endif //MATERIAL_H
