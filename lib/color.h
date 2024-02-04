//
// Created by sinat on 2/4/2024.
//

#ifndef COLOR_H
#define COLOR_H
#include "vec3.h"
#include "iostream"
using color = vec3;

void write_color(std::ostream& stream,color c)
{
    stream << static_cast<int>(255.999 * c.x()) << ' '
           << static_cast<int>(255.999 * c.y()) << ' '
           << static_cast<int>(255.999 * c.z()) << '\n';
}
#endif //COLOR_H
