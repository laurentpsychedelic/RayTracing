#ifndef SURFACE3D_HPP
#define SURFACE3D_HPP

#include "geometry/Range3D.hpp"
#include "geometry/LocalVector3D.hpp"

template <typename T>
class ISurface3D {
public:
    virtual Range3D<T> getRange() = 0;
    virtual bool intersects(const Point3D<T>& point) = 0;
    virtual LocalVector3D<T> getLocalVector(const Point3D<T>& point) = 0;
    /* Virtual destructor */
    virtual ~ISurface3D() {}
};

#endif
