#ifndef GRAPHICS_RAY_H
#define GRAPHICS_RAY_H


#include "Vec3.h"

class Ray {
private:
    Vec3 o;
    Vec3 d;
public:
    Ray(const Vec3 &o, const Vec3 &d);

    const Vec3 &getO() const;

    void setO(const Vec3 &o);

    const Vec3 &getD() const;

    void setD(const Vec3 &d);
};


#endif //GRAPHICS_RAY_H
