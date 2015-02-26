#ifndef POINTSOURCE_HPP
#define POINTSOURCE_HPP

#include "geometry/Point3D.hpp"

template <typename T, typename U>
class PointSource3D {
public:
    /* Members */
    const Point3D<T> location;
    const U intensity;
    /* Constructors */
    PointSource3D(const Point3D<T>& location, const U intensity) : location(location), intensity(intensity) {}
    PointSource3D(const PointSource3D<T, U>& point) : location(point.location), intensity(point.intensity) {}
    /* Friend functions */
    template <typename V, typename W>
    friend std::ostream& operator<<(std::ostream& out, const PointSource3D<V, W>& instance);
};

template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const PointSource3D<T,U>& instance) {
    return out << "<" << instance.intensity << "@" << instance.location << ">";
}

#endif
