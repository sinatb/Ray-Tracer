#include <iostream>

using namespace std;
int main() {
    //Image
    int width = 256;
    int height = 256;


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

            cout << "r : " << ir << " g : " << ig << " b : " << ib << '\n';
        }
    }
    return 0;
}
