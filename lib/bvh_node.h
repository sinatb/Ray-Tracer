//
// Created by sinat on 5/16/2024.
//

#ifndef RAY_TRACER_BVH_NODE_H
#define RAY_TRACER_BVH_NODE_H

#include <algorithm>
#include "hittable_list.h"
class bvh_node : public hittable{
public:
    bvh_node();

    bvh_node(hittable_list& list)
            : bvh_node(list.objects, 0, list.objects.size())
    {}

    bvh_node(std::vector<shared_ptr<hittable>>& src_objects,size_t start, size_t end)
    {
        auto objects = src_objects; // Create a modifiable array of the source scene objects

        int axis = random_int(0,2);
        auto comparator = (axis == 0) ? box_x_compare
                                      : (axis == 1) ? box_y_compare
                                                    : box_z_compare;

        size_t object_span = end - start;

        if (object_span == 1) {
            left = right = objects[start];
        } else if (object_span == 2) {
            if (comparator(objects[start], objects[start+1])) {
                left = objects[start];
                right = objects[start+1];
            } else {
                left = objects[start+1];
                right = objects[start];
            }
        } else {
            std::sort(objects.begin() + start, objects.begin() + end, comparator);

            auto mid = start + object_span/2;
            left = make_shared<bvh_node>(objects, start, mid);
            right = make_shared<bvh_node>(objects, mid, end);
        }

        aabb box_left, box_right;

        if (  !left->bounding_box (box_left)
              || !right->bounding_box( box_right)
                )
            std::cerr << "No bounding box in bvh_node constructor.\n";

        box = hittable_list::surrounding_box(box_left, box_right);
    };

    bool hit (ray& r, interval ray_i, hit_record& rec) const override;

    bool bounding_box(aabb& output_box) const override;

private:
        shared_ptr<hittable> left;
        shared_ptr<hittable> right;
        aabb box;
        static bool box_compare(
                const shared_ptr<hittable> a, const shared_ptr<hittable> b, int axis_index
        ) {
            auto a_axis_interval = a->bounding_box().axis_interval(axis_index);
            auto b_axis_interval = b->bounding_box().axis_interval(axis_index);
            return a_axis_interval.min < b_axis_interval.min;
        }

        static bool box_x_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
            return box_compare(a, b, 0);
        }

        static bool box_y_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
            return box_compare(a, b, 1);
        }

        static bool box_z_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
            return box_compare(a, b, 2);
        }
};

bool bvh_node::bounding_box(aabb& output_box) const {
    output_box = box;
    return true;
}
bool bvh_node::hit(ray& r, interval ray_i, hit_record& rec) const {
    if (!box.hit(r, ray_i.min, ray_i.max))
        return false;
    bool hit_left = left->hit(r, ray_i, rec);
    auto r_interval = hit_left ? interval{ray_i.min, rec.t} : ray_i;
    bool hit_right = right->hit(r, r_interval, rec);
    return hit_left || hit_right;
}

#endif //RAY_TRACER_BVH_NODE_H
