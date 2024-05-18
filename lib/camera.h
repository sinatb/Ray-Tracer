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
    double vfov = 90;
    point3 lookfrom = point3(0,0,-1);
    point3 lookat   = point3(0,0,0);
    vec3   vup      = vec3(0,1,0);

    void render(const hittable& world, const color background){
        init();
        const double sampling_factor = 500;
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
                    auto c = ray_color(r, world,background,max_depth);

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
        stbi_write_png("../Images/final-bvh.png",width,height,3,image_data,width*3);
    }
private:
    int width{},height{};
    double focal_length{},viewport_width{},ratio{},viewport_height{};
    point3 camera_center;
    vec3 u_delta,v_delta,pixel0_loc;
    interval valid_range;
    vec3   u, v, w;

    void init(){
        width = 1200;
        ratio = 16.0/9.0;
        valid_range = interval(0.0,0.999999);
        height = static_cast<int>((1/ratio)*width);

        camera_center = lookfrom;

        focal_length = focal_length = (lookfrom - lookat).length();
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        viewport_height = 2 * h * focal_length;
        viewport_width = viewport_height * (static_cast<double>(width)/ height);

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        auto vp_u = viewport_width * u;
        auto vp_v = viewport_height * -v;

        u_delta = vp_u/width;
        v_delta = vp_v/height;

        auto vp_tl = camera_center - (focal_length * w) - vp_u/2 - vp_v/2;
        pixel0_loc = vp_tl + (u_delta+v_delta)/2;
    }
    static color ray_color(ray& r, const hittable& world,const color background, int depth){
        hit_record h;
        if (depth <= 0)
            return {0,0,0};
        if (world.hit(r,interval(0.0001,infinity),h))
        {
            ray scattered;
            color attenuation;
            color emitted = h.mat->emitted();
            if (h.mat->scatter(r,h,attenuation,scattered)) {
                return attenuation * ray_color(scattered,world,background,depth-1);
            }
            return emitted;
        }else{
            return background;
        }
        auto a = (r.get_direction().x() + 1.0)*0.5;
        auto c = a*color(1.0,1.0,1.0) + (1-a)*color (0.5,0.5,1.0);
        return c;
    }
};
#endif //CAMERA_H
