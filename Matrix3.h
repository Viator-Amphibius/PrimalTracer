//
// Created by khale on 19-Nov-18.
//

#ifndef GRAPHICS_MATRIX3_H
#define GRAPHICS_MATRIX3_H


#include "Vec3.h"

class Matrix3 {
private:
    Vec3 V1;
    Vec3 V2;
    Vec3 V3;
public:
    Matrix3(const Vec3 &V1, const Vec3 &V2, const Vec3 &V3);
    double operator!() const; //returns the determinant
    Vec3 operator^(const Vec3& Z) const;
};


#endif //GRAPHICS_MATRIX3_H
