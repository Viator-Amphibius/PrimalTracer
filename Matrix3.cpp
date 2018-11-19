//
// Created by khale on 19-Nov-18.
//

#include "Matrix3.h"

Matrix3::Matrix3(const Vec3 &V1, const Vec3 &V2, const Vec3 &V3) : V1(V1), V2(V2), V3(V3) {}

double Matrix3::operator!() const {
    //return the determinant
    double a = V1.getX() * (V2.getY()*V3.getZ() - V2.getZ()*V3.getY());
    double b = V2.getX() * (V1.getY()*V3.getZ() - V1.getZ()*V3.getY());
    double c = V3.getX() * (V1.getY()*V2.getZ() - V1.getZ()*V2.getY());
    return a-b+c;
}

Vec3 Matrix3::operator^(const Vec3 &Z) const {
    //Matrix * P = Z, we will calculate P
    Vec3 P(0,0,0);
    double MatrixDet = !(*this);
    if(MatrixDet == 0) //just a precaution, the user should check the determinant before using this operation
        return P;
    P.setX(!Matrix3(Vec3(Z),Vec3(this->V2),Vec3(this->V3)) / MatrixDet);
    P.setY(!Matrix3(Vec3(this->V1),Vec3(Z),Vec3(this->V3)) / MatrixDet);
    P.setZ(!Matrix3(Vec3(this->V1),Vec3(this->V2),Vec3(Z)) / MatrixDet);
    return P;
}
