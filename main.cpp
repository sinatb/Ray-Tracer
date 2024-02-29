#include <iostream>

#include "./lib/hittable_list.h"
#include "./lib/sphere.h"
#include "./lib/camera.h"
#include "./lib/material.h"
#include "./lib/color.h"

using namespace std;
int main() {

    //object creation on scene
    hittable_list world;
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8),0.1);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2),1.0);




    world.add(make_shared<sphere>(point3(0,0,-1), 0.3,material_center));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100,material_ground));
    world.add(make_shared<sphere>(point3(-0.7,    0.0, -1.0),   0.3, material_left));
    world.add(make_shared<sphere>(point3( 0.7,    0.0, -1.0),   0.3, material_right));
    //
    camera c;
    c.render(world);
    return 0;
}
