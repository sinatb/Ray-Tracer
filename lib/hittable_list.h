//
// Created by sinat on 2/10/2024.
//

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "commons.h"
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
        bbox = aabb(bbox, obj->bounding_box());

    }


    bool hit(ray &r, interval ray_i, hit_record &h) const override{
        hit_record tmp_h;
        bool hit_anything = false;
        auto closest_so_far = ray_i.max;

        for (const auto& object : objects){
            if (object->hit(r,interval(ray_i.min,closest_so_far),tmp_h)){
                hit_anything = true;
                closest_so_far = tmp_h.t;
                h = tmp_h;
            }
        }
        return hit_anything;
    }
    static aabb surrounding_box(aabb box0, aabb box1) {
        point3 small(fmin(box0.minimum.x(), box1.minimum.x()),
                     fmin(box0.minimum.y(), box1.minimum.y()),
                     fmin(box0.minimum.z(), box1.minimum.z()));

        point3 big(fmax(box0.maximum.x(), box1.maximum.x()),
                   fmax(box0.maximum.y(), box1.maximum.y()),
                   fmax(box0.maximum.z(), box1.maximum.z()));

        return {small,big};
    }
    [[nodiscard]] aabb bounding_box() const override{
        return bbox;
    }
private:
    aabb bbox;
};
#endif //HITTABLE_LIST_H
