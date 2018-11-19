//
// Created by khale on 18-Nov-18.
//

#include "Camera.h"

Camera::Camera(const Vec3 &e, const Vec3 &gaze, const Vec3 &v, double l, double r, double b, double t, double d,
               int sizeX, int sizeY) : e(e) , gaze(gaze), v(v), u(u)
{
    this->l = l;
    this->r = r;
    this->b = b;
    this->t = t;
    this->d = d;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->pixelW = (r-l)/(double)sizeX;
    this->pixelH = (t-b)/(double)sizeY;
    this->halfPixelW = this->pixelW/2.0;
    this->halfPixelH = this->pixelH/2.0;

    this->u = this->gaze ^ this->v;
    this->u.normalize();

    this->v = this->u ^ this->gaze;
    this->v.normalize();

    this->gaze.normalize();
}

ostream& operator<< (ostream& stream, const Camera& c)
{
    stream << c.e << endl;
    stream << c.gaze << endl;
    stream << c.v << endl;
    stream << c.u << endl;
    stream << c.l << endl;
    stream << c.r << endl;
    stream << c.b << endl;
    stream << c.t << endl;
    stream << c.d << endl;
    stream << c.sizeX << endl;
    stream << c.sizeY << endl;
    stream << c.pixelW << endl;
    stream << c.pixelH << endl;
    stream << c.halfPixelW << endl;
    stream << c.halfPixelH << endl;
    return stream;
}

const Vec3 &Camera::getE() const {
    return e;
}

void Camera::setE(const Vec3 &e) {
    Camera::e = e;
}

const Vec3 &Camera::getGaze() const {
    return gaze;
}

void Camera::setGaze(const Vec3 &gaze) {
    Camera::gaze = gaze;
}

const Vec3 &Camera::getV() const {
    return v;
}

void Camera::setV(const Vec3 &v) {
    Camera::v = v;
}

const Vec3 &Camera::getU() const {
    return u;
}

void Camera::setU(const Vec3 &u) {
    Camera::u = u;
}

double Camera::getL() const {
    return l;
}

void Camera::setL(double l) {
    Camera::l = l;
}

double Camera::getR() const {
    return r;
}

void Camera::setR(double r) {
    Camera::r = r;
}

double Camera::getB() const {
    return b;
}

void Camera::setB(double b) {
    Camera::b = b;
}

double Camera::getT() const {
    return t;
}

void Camera::setT(double t) {
    Camera::t = t;
}

double Camera::getD() const {
    return d;
}

void Camera::setD(double d) {
    Camera::d = d;
}

int Camera::getSizeX() const {
    return sizeX;
}

void Camera::setSizeX(int sizeX) {
    Camera::sizeX = sizeX;
}

int Camera::getSizeY() const {
    return sizeY;
}

void Camera::setSizeY(int sizeY) {
    Camera::sizeY = sizeY;
}

double Camera::getPixelW() const {
    return pixelW;
}

void Camera::setPixelW(double pixelW) {
    Camera::pixelW = pixelW;
}

double Camera::getPixelH() const {
    return pixelH;
}

void Camera::setPixelH(double pixelH) {
    Camera::pixelH = pixelH;
}

double Camera::getHalfPixelW() const {
    return halfPixelW;
}

void Camera::setHalfPixelW(double halfPixelW) {
    Camera::halfPixelW = halfPixelW;
}

double Camera::getHalfPixelH() const {
    return halfPixelH;
}

void Camera::setHalfPixelH(double halfPixelH) {
    Camera::halfPixelH = halfPixelH;
}
