//
// Created by khale on 18-Nov-18.
//

#include "Ray.h"

Ray::Ray(const Vec3 &o, const Vec3 &d) : o(o), d(d) {}

const Vec3 &Ray::getO() const {
    return o;
}

void Ray::setO(const Vec3 &o) {
    Ray::o = o;
}

const Vec3 &Ray::getD() const {
    return d;
}

void Ray::setD(const Vec3 &d) {
    Ray::d = d;
}
