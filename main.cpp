#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "./lib/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./lib/stb_image_write.h"

using namespace std;
int main() {
    //Image
    int width = 256;
    int height = 256;

    uint8_t image_data[width*height*3];
    //Render
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            auto r = double(i) / (height+1);
            auto g = 0;
            auto b=double (j) / (width+1);

            int ir = static_cast<int>(255.999*r);
            int ig = static_cast<int>(255.999*g);
            int ib = static_cast<int>(255.999*b);

            image_data[i*width*3 + j*3] = ir;
            image_data[i*width*3 + j*3 + 1] = ig;
            image_data[i*width*3 + j*3 + 2] = ib;

        }
    }
    stbi_write_png("../Images/first_image.png",width,height,3,image_data,width*3);
    return 0;
}
