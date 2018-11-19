//
// Created by khale on 18-Nov-18.
//

#ifndef GRAPHICS_CAMERA_H
#define GRAPHICS_CAMERA_H


#include "Vec3.h"

class Camera {
private:
    Vec3 e;
    Vec3 gaze;
    Vec3 v;
    Vec3 u;
    double l;
    double r;
    double b;
    double t;
    double d;
    int sizeX;
    int sizeY;
    double pixelW;
    double pixelH;
    double halfPixelW;
    double halfPixelH;
public:
    Camera(const Vec3 &e, const Vec3 &gaze, const Vec3 &v, double l, double r, double b, double t, double d, int sizeX,
           int sizeY);
    friend ostream& operator<< (ostream& stream, const Camera& c);

    const Vec3 &getE() const;

    void setE(const Vec3 &e);

    const Vec3 &getGaze() const;

    void setGaze(const Vec3 &gaze);

    const Vec3 &getV() const;

    void setV(const Vec3 &v);

    const Vec3 &getU() const;

    void setU(const Vec3 &u);

    double getL() const;

    void setL(double l);

    double getR() const;

    void setR(double r);

    double getB() const;

    void setB(double b);

    double getT() const;

    void setT(double t);

    double getD() const;

    void setD(double d);

    int getSizeX() const;

    void setSizeX(int sizeX);

    int getSizeY() const;

    void setSizeY(int sizeY);

    double getPixelW() const;

    void setPixelW(double pixelW);

    double getPixelH() const;

    void setPixelH(double pixelH);

    double getHalfPixelW() const;

    void setHalfPixelW(double halfPixelW);

    double getHalfPixelH() const;

    void setHalfPixelH(double halfPixelH);
};


#endif //GRAPHICS_CAMERA_H
