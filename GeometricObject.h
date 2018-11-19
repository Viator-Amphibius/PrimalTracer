

#ifndef GRAPHICS_GEOMETRICOBJECT_H
#define GRAPHICS_GEOMETRICOBJECT_H


#include "Color.h"
#include "Ray.h"

class GeometricObject {
private:
    Color color;
public:
    const Color &getColor() const;

    void setColor(const Color &color);

    GeometricObject();
    GeometricObject(const Color &color);
    virtual bool hitMe(double& t, const Ray& ray) = 0;
};


#endif //GRAPHICS_GEOMETRICOBJECT_H
