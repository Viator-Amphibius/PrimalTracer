#include "Vec3.h"

bool cmpDouble(double n, double m)
{
    return (fabs(n-m)<0.000000001);
}

Vec3::Vec3(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
};

Vec3::Vec3(const Vec3& v2)
{
    this->x = v2.x;
    this->y = v2.y;
    this->z = v2.z;
};

Vec3& Vec3::operator=(const Vec3& v2)
{
    if(this == &v2)
        return *this;

    this->x = v2.x;
    this->y = v2.y;
    this->z = v2.z;
    return *this;
}

Vec3 Vec3::operator+ (const Vec3& v2) const
{
    return Vec3(x+v2.x, y+v2.y, z+v2.z);
}
Vec3 Vec3::operator- (const Vec3& v2) const
{
    return Vec3(x-v2.x, y-v2.y, z-v2.z);
}
double Vec3::operator* (const Vec3& v2) const
{
    return (x*v2.x + y*v2.y+ z*v2.z);
}
Vec3 Vec3::operator^ (const Vec3& v2) const
{
    return Vec3(y*v2.z - z*v2.y, z*v2.x - x*v2.z, x*v2.y - y*v2.x);
}
Vec3 Vec3::operator% (double cnst) const
{
    return Vec3(cnst*x,cnst*y,cnst*z);
}
double Vec3::length()
{
    return sqrt(x*x+y*y+z*z);
}
void Vec3::normalize()
{
    double lengthBeforeNormalizing = this->length();
    x = x/lengthBeforeNormalizing;
    y = y/lengthBeforeNormalizing;
    z = z/lengthBeforeNormalizing;
}
bool Vec3::operator== (const Vec3& v2) const
{
    return (cmpDouble(x,v2.x)&&cmpDouble(y,v2.y)&&cmpDouble(z,v2.z));
}
double Vec3::operator| (const Vec3& v2) const
{
    return sqrt(pow(x-v2.x,2)+pow(y-v2.y,2)+pow(z-v2.z,2));
}
ostream& operator<< (ostream& stream, const Vec3& v)
{
    stream << "(" << v.x << "," << v.y << "," << v.z << ")";
    return stream;
}

double Vec3::getX() const {
    return x;
}

void Vec3::setX(double x) {
    Vec3::x = x;
}

double Vec3::getY() const {
    return y;
}

void Vec3::setY(double y) {
    Vec3::y = y;
}

double Vec3::getZ() const {
    return z;
}

void Vec3::setZ(double z) {
    Vec3::z = z;
}

Vec3::~Vec3() {

}
