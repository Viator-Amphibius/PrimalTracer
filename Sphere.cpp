#include "Sphere.h"

Sphere::Sphere(Vec3 Center, double Radius, Color SphereColor) : GeometricObject(SphereColor), center(Center)
{
    r = Radius;
}
bool Sphere::hitMe(double &t, const Ray &ray)
{
    double A = ray.getD() * ray.getD();
    double B = 2 * (ray.getD() * (ray.getO()-center));
    double C = ((ray.getO()-center)*(ray.getO()-center)) - r*r;
    double delta = B*B - 4*A*C;
    if(delta < 0)
        return false;
    else //also includes delta==0 (avoided implementing separately not to worry about double comparison)
    {
        t = (-1.0*B - sqrt(delta))/(2.0*A);
        if(t>=1)
            return true;
        t = (-1.0*B + sqrt(delta))/(2.0*A);
        if(t>=1)
            return true;
        else
            return false;
    }
}

const Vec3 &Sphere::getCenter() const {
    return center;
}

void Sphere::setCenter(const Vec3 &center) {
    Sphere::center = center;
}

double Sphere::getR() const {
    return r;
}

void Sphere::setR(double r) {
    Sphere::r = r;
}

Vec3 Sphere::getNormal(const Vec3 &point) {
    Vec3 normal(point-center);
    normal.normalize();
    return normal;
}
