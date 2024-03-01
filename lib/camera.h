//
// Created by sinat on 2/17/2024.
//

#ifndef CAMERA_H
#define CAMERA_H

#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./stb_image_write.h"

#include "material.h"
#include "commons.h"
#include "hittable.h"
#include "color.h"

using namespace std;
inline double linear_to_gamma(double linear_component)
{
    return sqrt(linear_component);
}
class camera{
public:
    void render(const hittable& world){
        init();
        const double sampling_factor = 10;
        int max_depth = 50;
        uint8_t image_data[width*height*3];
        for (int i=0; i<height; i++)
        {
            clog <<'\r'<< "Progress : " << i << " / " << height << " " << flush;
            for (int j=0; j<width; j++)
            {
                double tmp_r ,tmp_g,tmp_b ;
                tmp_r = tmp_g = tmp_b = 0.0;
                auto point = pixel0_loc + (i * v_delta + j * u_delta);

                for (int sample = 0 ; sample < sampling_factor ; sample++)
                {
                    auto dx = random_double() + -0.5;
                    auto dy = random_double() + -0.5;
                    auto sample_point = point + dx*u_delta + dy*v_delta;
                    auto direction_pointer = sample_point - camera_center;
                    direction_pointer = unit_vector(direction_pointer);
                    ray r(camera_center, direction_pointer);
                    auto c = ray_color(r, world,max_depth);

                    tmp_r = valid_range.clamp(tmp_r + linear_to_gamma(c.x())/sampling_factor);
                    tmp_g = valid_range.clamp(tmp_g + linear_to_gamma(c.y())/sampling_factor);
                    tmp_b = valid_range.clamp(tmp_b + linear_to_gamma(c.z())/sampling_factor);
                }
                int ir = static_cast<int>(255.999 * tmp_r);
                int ig = static_cast<int>(255.999 * tmp_g);
                int ib = static_cast<int>(255.999 * tmp_b);
                image_data[i * width * 3 + j * 3] += ir;
                image_data[i * width * 3 + j * 3 + 1] += ig;
                image_data[i * width * 3 + j * 3 + 2] += ib;
            }
        }
        stbi_write_png("../Images/dielectric_schlick.png",width,height,3,image_data,width*3);
    }
private:
    int width{},height{};
    double focal_length{},viewport_width{},ratio{},viewport_height{};
    point3 camera_center;
    vec3 u_delta,v_delta,pixel0_loc;
    interval valid_range;
    void init(){
        width = 1200;
        ratio = 16.0/9.0;
        valid_range = interval(0.0,0.999999);
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
    static color ray_color(ray& r, const hittable& world, int depth){
        hit_record h;
        if (depth <= 0)
            return {0,0,0};
        if (world.hit(r,interval(0.0001,infinity),h))
        {
            ray scattered;
            color attenuation;
            if (h.mat->scatter(r,h,attenuation,scattered)) {
                return attenuation * ray_color(scattered,world,depth-1);
            }
            return {0,0,0};
        }
        auto a = (r.get_direction().x() + 1.0)*0.5;
        auto c = a*color(1.0,1.0,1.0) + (1-a)*color (0.5,0.5,1.0);
        return c;
    }
};
#endif //CAMERA_H
