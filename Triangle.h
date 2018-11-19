#ifndef GRAPHICS_TRIANGLE_H
#define GRAPHICS_TRIANGLE_H


#include "GeometricObject.h"

class Triangle : public GeometricObject{
private:
    Vec3 A;
    Vec3 B;
    Vec3 C;
public:
    Triangle(const Color &color, const Vec3 &A, const Vec3 &B, const Vec3 &C);
    bool hitMe(double& t, const Ray& ray);

    const Vec3 &getA() const;

    void setA(const Vec3 &A);

    const Vec3 &getB() const;

    void setB(const Vec3 &B);

    const Vec3 &getC() const;

    void setC(const Vec3 &C);
};


#endif //GRAPHICS_TRIANGLE_H
