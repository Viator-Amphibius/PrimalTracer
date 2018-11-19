#include <math.h>
#include <iostream>
using namespace std;

#ifndef GRAPHICS_VEC3_H
#define GRAPHICS_VEC3_H

class Vec3
{
private:
    double x;
    double y;
    double z;
public:
    Vec3(double x, double y, double z);
    Vec3(const Vec3& v2);
    Vec3& operator=(const Vec3& v2);
    virtual ~Vec3();
    Vec3 operator+ (const Vec3& v2) const;
    Vec3 operator- (const Vec3& v2) const;
    double operator* (const Vec3& v2) const;
    Vec3 operator^ (const Vec3& v2) const;
    Vec3 operator% (double cnst) const;
    double length();
    void normalize();
    bool operator== (const Vec3& v2) const;
    double operator| (const Vec3& v2) const;
    friend ostream& operator<< (ostream& stream, const Vec3& v);

    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    double getZ() const;

    void setZ(double z);
};

#endif //GRAPHICS_VEC3_H
