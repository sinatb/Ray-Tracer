#include <iostream>

#include "./lib/hittable_list.h"
#include "./lib/sphere.h"
#include "./lib/camera.h"

using namespace std;
int main() {

    //object creation on scene
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.3));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
    //
    camera c;
    c.render(world);
    return 0;
}
