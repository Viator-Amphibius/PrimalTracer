#include "Light.h"

Light::Light(const Vec3 &pos, const Color &intensity) : pos(pos), intensity(intensity) {}

const Vec3 &Light::getPos() const {
    return pos;
}

void Light::setPos(const Vec3 &pos) {
    Light::pos = pos;
}

const Color &Light::getIntensity() const {
    return intensity;
}

void Light::setIntensity(const Color &intensity) {
    Light::intensity = intensity;
}

