#ifndef GRAPHICS_LIGHT_H
#define GRAPHICS_LIGHT_H


#include "Vec3.h"
#include "Color.h"

class Light {
private:
    Vec3 pos;
    Color intensity;
public:
    Light(const Vec3 &pos, const Color &intensity);

    const Vec3 &getPos() const;

    void setPos(const Vec3 &pos);

    const Color &getIntensity() const;

    void setIntensity(const Color &intensity);
};


#endif //GRAPHICS_LIGHT_H
