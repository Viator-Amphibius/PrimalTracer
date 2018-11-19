#ifndef GRAPHICS_SPHERE_H
#define GRAPHICS_SPHERE_H


#include "GeometricObject.h"

class Sphere : public GeometricObject{
private:
    Vec3 center;
    double r;
public:
    Sphere(Vec3 Center, double Radius, Color SphereColor);
    bool hitMe(double& t, const Ray& ray);
    Vec3 getNormal(const Vec3& point);

    const Vec3 &getCenter() const;

    void setCenter(const Vec3 &center);

    double getR() const;

    void setR(double r);
};


#endif //GRAPHICS_SPHERE_H
