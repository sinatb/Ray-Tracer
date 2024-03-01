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
    metal(const color& a, const double f) : albedo(a), fuzz(f) {}

    bool scatter(const ray& r_in, const hit_record& h, color& attenuation, ray& scattered)
    const override {
        vec3 reflected = reflect(unit_vector(unit_vector(r_in.get_direction())+random_unit_vector()*fuzz),
                                 h.normal);
        scattered = ray(h.hp, reflected);
        attenuation = albedo;
        return dot(scattered.get_direction(),reflected) > 0.0;
    }

private:
    double fuzz;
    color albedo;
};

class dielectric : public material{
public:
    explicit dielectric(double reflectance) : ir(reflectance){}

    bool scatter(const ray& r_in, const hit_record& h, color& attenuation, ray& scattered)
    const override{
        attenuation = color(1.0,1.0,1.0);

        double reflectance_ratio = h.front_face ? 1.0/ir : ir;

        auto unit_direction = unit_vector(r_in.get_direction());

        double cos_theta = fmin(dot(-unit_direction,h.normal),1.0);
        double sin_theta = sqrt(1-cos_theta*cos_theta);

        vec3 direction;

        if (sin_theta * reflectance_ratio <= 1.0)
            direction = refract(unit_direction,h.normal,reflectance_ratio);
        else
            direction = reflect(unit_direction,h.normal);

        scattered = ray(h.hp, unit_vector(direction));
        return true;
    }
private:
    double ir;
};
#endif //MATERIAL_H
