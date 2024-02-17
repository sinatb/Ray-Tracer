//
// Created by sinat on 2/17/2024.
//

#ifndef CAMERA_H
#define CAMERA_H

#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./stb_image_write.h"

#include "commons.h"
#include "hittable.h"
#include "color.h"

using namespace std;
class camera{
public:
    void render(const hittable& world){
        init();
        uint8_t image_data[width*height*3];
        for (int i=0; i<height; i++)
        {
            clog <<'\r'<< "Progress : " << i << " / " << height << " " << flush;
            for (int j=0; j<width; j++) {
                auto point = pixel0_loc + (i*v_delta + j*u_delta);
                auto direction_pointer = vec3(point - camera_center);
                auto direction = unit_vector(direction_pointer);
                ray r (point,direction);
                auto c = ray_color(r,world);

                int ir = static_cast<int>(255.999 * c.x());
                int ig = static_cast<int>(255.999 * c.y());
                int ib = static_cast<int>(255.999 * c.z());
                image_data[i * width * 3 + j * 3] = ir;
                image_data[i * width * 3 + j * 3 + 1] = ig;
                image_data[i * width * 3 + j * 3 + 2] = ib;
            }
        }
        stbi_write_png("../Images/world.png",width,height,3,image_data,width*3);
    }
private:
    int width{},height{};
    double focal_length{},viewport_width{},ratio{},viewport_height{};
    point3 camera_center;
    vec3 u_delta,v_delta,pixel0_loc;

    void init(){
        width = 800;
        ratio = 16.0/9.0;
        height = static_cast<int>((1/ratio)*width);

        focal_length = 1.0;
        viewport_width = 2.0;
        viewport_height = viewport_width * (static_cast<double>(height)/width);
        camera_center = point3(0,0,0);

        auto vp_u = vec3(viewport_width,0,0);
        auto vp_v = vec3(0,-viewport_height,0);

        u_delta = vp_u/width;
        v_delta = vp_v/height;

        auto vp_tl = camera_center - vec3(0,0,focal_length) - vp_u/2 - vp_v/2;
        pixel0_loc = vp_tl + (u_delta+v_delta)/2;
    }
    static color ray_color(ray& r, const hittable& world){
        hit_record h;
        if (world.hit(r,interval(-2,infinity),h))
        {
            return 0.5*(h.normal+color(1,1,1));
        }
        auto a = (r.get_direction().x() + 1.0)*0.5;
        auto c = a*color(1.0,1.0,1.0) + (1-a)*color (0.5,0.5,1.0);
        return c;
    }
};
#endif //CAMERA_H
