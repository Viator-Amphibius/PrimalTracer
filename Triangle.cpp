//
// Created by khale on 19-Nov-18.
//

#include "Triangle.h"
#include "Matrix3.h"

Triangle::Triangle(const Color &color, const Vec3 &A, const Vec3 &B, const Vec3 &C) : GeometricObject(color), A(A),
                                                                                      B(B), C(C) {}

bool Triangle::hitMe(double &t, const Ray &ray) {
    Matrix3 matrix(Vec3(ray.getD()),Vec3(A-B),Vec3(A-C));
    if((!matrix) == 0) //checks if the determinant is zero
        return false;
    Vec3 CramerResult = matrix ^ Vec3(A-ray.getO());
    t = CramerResult.getX();
    double beta = CramerResult.getY();
    double gamma = CramerResult.getZ();
    return (t>=1 && beta>=0 && gamma>=0 && (beta+gamma)<=1);
}

const Vec3 &Triangle::getA() const {
    return A;
}

void Triangle::setA(const Vec3 &A) {
    Triangle::A = A;
}

const Vec3 &Triangle::getB() const {
    return B;
}

void Triangle::setB(const Vec3 &B) {
    Triangle::B = B;
}

const Vec3 &Triangle::getC() const {
    return C;
}

void Triangle::setC(const Vec3 &C) {
    Triangle::C = C;
}

Vec3 Triangle::getNormal(const Vec3 &point) {
    Vec3 normal((B-A) ^ (C-A));
    normal.normalize();
    return normal;
}
