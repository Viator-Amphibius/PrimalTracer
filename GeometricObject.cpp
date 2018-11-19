//
// Created by khale on 18-Nov-18.
//

#include "GeometricObject.h"

GeometricObject::GeometricObject() : color() {}
GeometricObject::GeometricObject(const Color &color) : color(color) {}

const Color &GeometricObject::getColor() const {
    return color;
}

void GeometricObject::setColor(const Color &color) {
    GeometricObject::color = color;
}
