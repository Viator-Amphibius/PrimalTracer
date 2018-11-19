#include <iostream>
using namespace std;

#ifndef GRAPHICS_COLOR_H
#define GRAPHICS_COLOR_H


class Color {
private:
    double r;
    double g;
    double b;
public:
    Color();
    Color(double r, double g, double b);
    Color(int r, int g, int b);
    friend ostream& operator<< (ostream& stream, const Color& c);
    double getR() const;

    void setR(double r);

    double getG() const;

    void setG(double g);

    double getB() const;

    void setB(double b);
};


#endif //GRAPHICS_COLOR_H
