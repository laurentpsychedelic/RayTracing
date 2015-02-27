#ifndef SPHERICALSURFACEPROPAGATOR_HPP
#define SPHERICALSURFACEPROPAGATOR_HPP

#include <cmath>
#include "geometry/SphericalSurface3D.hpp"
#include "geometry/Utils.hpp"
#include "optics/IPropagator.hpp"

template <typename T, typename U>
class SphericalSurfacePropagator : public IPropagator<T, U> {
public:
    /* Member functions */
    virtual const Ray<T, U> propagate(const Ray<T, U>& ray, ISurface3D<T>* surface);
    /* Virtual destructor */
    virtual ~SphericalSurfacePropagator() {}
};

template <typename T, typename U>
const Ray<T, U> SphericalSurfacePropagator<T, U>::propagate(const Ray<T, U>& ray, ISurface3D<T>* _surface) {
    if (ray.direction.z <= 0) // The ray is lost
        return Ray<T, U>(ray.location, ray.direction, 0.0); // 0 intensity
    const SphericalSurface3D<T>* surface = dynamic_cast<SphericalSurface3D<T>* >(_surface);
    if (!surface)
        throw "Surface is not a spherical surface!! (spherical surface propagator)";
    const Range<T> range = surface->getRange().rangeX;
    const Vector3D<T> direction = ray.direction;
    const Point3D<T> start = ray.location;
    T _r = (T) sqrt(start.x * start.x + start.y * start.y);
    if (_r >= surface->radius && Utils::IsGettingFarFromOpticalAxis(start, direction)) // The ray is lost!
        return Ray<T, U>(start, direction, 0.0); // 0 intensity
    // Calculate propagation point at the x-range left border
    const T xleft = range.start;
    Point3D<T> prop = start + (xleft - start.x) * direction;
    _r = (T) sqrt(prop.x * prop.x + prop.y * prop.y);
    if (_r >= surface->radius && Utils::IsGettingFarFromOpticalAxis(prop, direction)) // The ray is lost!
        return Ray<T, U>(start, direction, 0.0); // 0 intensity
    // Compute the intersection of the ray with the spherical surface
    throw "Not yet implemented!";
}

#endif
