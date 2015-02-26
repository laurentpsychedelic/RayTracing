#ifndef SPHERICALSURFACE3D_HPP
#define SPHERICALSURFACE3D_HPP

#include <cmath>

using namespace std;

template <typename T>
class SphericalSurface3D : public ISurface3D<T> {
public:
    Range3D<T> getRange();
    virtual LocalVector3D<T> getNormalVector(const Point3D<T>& point);
    /* Members */
private:
    const Point3D<T> center;
    const T curvature;
    const T radius;
public:
    /* Constructors */
    SphericalSurface3D(const Point3D<T>& center, const T curvature, const T radius) : center(center), curvature(curvature), radius(radius) {}
    /* Friend functions */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const SphericalSurface3D<U>& instance);
};

template <typename T>
Range3D<T> SphericalSurface3D<T>::getRange() {
    const T thickness = (T) asin(abs((double) curvature) / (double) radius);
    if (curvature > 0) {
        return Range3D<T>(Range<T>(center.x - radius, center.x + radius) /* range x */,
                          Range<T>(center.y - radius, center.y + radius) /* range y */,
                          Range<T>(center.z + radius - thickness, center.z + radius) /* range z */);
    } else { // curvature < 0
        return Range3D<T>(Range<T>(center.x - radius, center.x + radius) /* range x */,
                          Range<T>(center.y - radius, center.y + radius) /* range y */,
                          Range<T>(center.z - radius, center.z - radius + thickness) /* range z */);
    }
}

template <typename T>
LocalVector3D<T> SphericalSurface3D<T>::getNormalVector(const Point3D<T>& point) {
    throw "Not yet implemented!";
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const SphericalSurface3D<T>& instance) {
    return out << "[[ center: " << instance.center << ", curvature: " << instance.curvature << ", radius: " << instance.radius << " ]]";
}

#endif
