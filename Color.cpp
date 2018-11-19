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
    Color::r = r;
}

double Color::getG() const {
    return g;
}

void Color::setG(double g) {
    Color::g = g;
}

double Color::getB() const {
    return b;
}

void Color::setB(double b) {
    Color::b = b;
}
