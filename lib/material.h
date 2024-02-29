//
// Created by sinat on 2/28/2024.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "commons.h"
class hit_record;

class material{

public:
    virtual ~material() = default;

    virtual bool scatter(const ray& r_in,const hit_record& h, color& attenuation, ray& scattered) = 0;
};


#endif //MATERIAL_H
