//
// Created by sinat on 2/10/2024.
//

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include "memory"
#include "vector"

using std::shared_ptr;
using std::make_shared;


class hittable_list : public hittable{
public:
    std::vector<shared_ptr<hittable>> objects;

    hittable_list() = default;
    explicit hittable_list(const shared_ptr<hittable>& obj){
        add(obj);
    }

    void clear(){
        objects.clear();
    }
    void add(const shared_ptr<hittable>& obj){
        objects.push_back(obj);
    }


    bool hit(ray &r, double t_min, double t_max, hit_record &h) const override{
        hit_record tmp_h;
        bool hit_anything = false;
        auto closest_so_far = t_max;

        for (const auto& object : objects){
            if (object->hit(r,t_min,closest_so_far,tmp_h)){
                hit_anything = true;
                closest_so_far = tmp_h.t;
                h = tmp_h;
            }
        }
        return hit_anything;
    }
};



#endif //HITTABLE_LIST_H
