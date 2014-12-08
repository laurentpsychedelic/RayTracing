#ifndef RAY_HPP
#define RAY_HPP

#include <iostream>
#include "geometry/Point3D.hpp"
#include "geometry/Vector3D.hpp"

template <typename T, typename U>
class Ray
{
public:
    /* Members */
    const Point3D<T> location;
    const Vector3D<T> direction;
    const U intensity;
    /* Constructors */
    Ray(const Point3D<T>& location, const Vector3D<T>& direction, U intensity) : location(location), direction(direction), intensity(intensity) {}
    /* Friend functions */
    template <typename V, typename W>
    friend std::ostream& operator<<(std::ostream& out, const Ray<V, W>& instance);
};

template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const Ray<T, U>& instance) {
    return out << "{ intensity: " << instance.intensity << ", location: " << instance.location << ", direction: " << instance.direction << " }";
}

#endif
