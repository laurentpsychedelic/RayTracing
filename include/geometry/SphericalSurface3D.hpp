#ifndef SPHERICALSURFACE3D_HPP
#define SPHERICALSURFACE3D_HPP

#include <cmath>
#include "geometry/Point3D.hpp"
#include "geometry/Range3D.hpp"
#include "geometry/LocalVector3D.hpp"
#include "geometry/ISurface3D.hpp"

using namespace std;

template <typename T>
class SphericalSurface3D : public ISurface3D<T> {
public:
    const Range3D<T> getRange() const;
    virtual LocalVector3D<T> getNormalVector(const Point3D<T>& point);
    /* Members */
public:
    const Point3D<T> center;
    const T curvature;
    const T radius;
public:
    /* Constructors */
    SphericalSurface3D(const Point3D<T>& center, const T curvature, const T radius) : center(center), curvature(curvature), radius(radius) {
        check(center, curvature, radius);
    }
    /* Friend functions */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const SphericalSurface3D<U>& instance);
private:
    void check(const Point3D<T>& center, const T curvature, const T radius);
};

template <typename T>
const Range3D<T> SphericalSurface3D<T>::getRange() const {
    const T thickness = (T) asin((double) radius / abs((double) curvature));
    if (curvature > 0) {
        return Range3D<T>(Range<T>(center.x - radius, center.x + radius) /* range x */,
                          Range<T>(center.y - radius, center.y + radius) /* range y */,
                          Range<T>(center.z + curvature - thickness, center.z + curvature) /* range z */);
    } else { // curvature < 0
        return Range3D<T>(Range<T>(center.x - radius, center.x + radius) /* range x */,
                          Range<T>(center.y - radius, center.y + radius) /* range y */,
                          Range<T>(center.z + curvature, center.z + curvature + thickness) /* range z */);
    }
}

template <typename T>
LocalVector3D<T> SphericalSurface3D<T>::getNormalVector(const Point3D<T>& _point) {
    const double localX = (double) (_point.x - center.x);
    const double localY = (double) (_point.y - center.y);
    const double localZ = (curvature > 0 ? 1.0 : -1.0) * sqrt(curvature * curvature - localX * localX - localY * localY);
    Point3D<T> point(_point.x, _point.y, center.z + localZ);
    return LocalVector3D<T>(point, !(Vector3D<T>(point.x - center.x, point.y - center.y, point.z - center.z)));
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const SphericalSurface3D<T>& instance) {
    return out << "[[ center: " << instance.center << ", curvature: " << instance.curvature << ", radius: " << instance.radius << " ]]";
}

template <typename T>
void SphericalSurface3D<T>::check(const Point3D<T>& center, const T curvature, const T radius) {
    if (radius != radius || curvature != curvature)
        throw "Invalid radius or curvature (NaN)!";
    if (radius <= 0)
        throw "The radius of a spherical surface must be strictly greater than 0!";
    if (curvature == 0.0)
        throw "The curvature of a spherical surface must be strictly positive or negative, i.e. not equal to 0!";
    if (abs(radius) > abs(curvature))
        throw "The radius of a spherical surface must be less than or equal to its curvature (in absolute value)!";
}

#endif
