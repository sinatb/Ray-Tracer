#include <iostream>

#include "./lib/hittable_list.h"
#include "./lib/bvh_node.h"
#include "./lib/sphere.h"
#include "./lib/camera.h"
#include "./lib/material.h"
#include "./lib/color.h"

using namespace std;
int main() {

    //object creation on scene
    hittable_list world;
    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;
                if (choose_mat < 0.2){
                    sphere_material = make_shared<diffuse_light>(color(1,0.85,0.72));
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));

                } else if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random_vector(0.0,1.0) * color::random_vector(0.0,1.0);
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random_vector(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
    world = hittable_list(make_shared<bvh_node>(world));

    //
    camera c;
    c.vfov     = 20;
    c.lookfrom = point3(13,2,3);
    c.lookat   = point3(0,0,0);
    c.vup      = vec3(0,1,0);
    c.render(world,color(0.0, 0.0, 0.0));
    return 0;
}
