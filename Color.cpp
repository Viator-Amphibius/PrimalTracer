//
// Created by khale on 18-Nov-18.
//

#include "Color.h"

Color::Color()
{
    this->r = 0.0;
    this->g = 0.0;
    this->b = 0.0;
}

Color::Color(double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color(int r, int g, int b)
{
    this->r = r/255.0;
    this->g = g/255.0;
    this->b = b/255.0;
}

ostream& operator<< (ostream& stream, const Color& c)
{
    stream << (int)(c.r*255) << " " << (int)(c.g*255) << " " << (int)(c.b*255) << " ";
    return stream;
}

double Color::getR() const {
    return r;
}

void Color::setR(double r) {
    if(r>1) Color::r = 1;
    else if(r<0) Color::r = 0;
    else Color::r = r;
}

double Color::getG() const {
    return g;
}

void Color::setG(double g) {
    if(g>1) Color::g = 1;
    else if(g<0) Color::g = 0;
    else Color::g = g;
}

double Color::getB() const {
    return b;
}

void Color::setB(double b) {
    if(b>1) Color::b = 1;
    else if(b<0) Color::b = 0;
    else Color::b = b;
}
