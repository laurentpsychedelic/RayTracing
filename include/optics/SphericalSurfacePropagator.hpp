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
    const Range<T> range = surface->getRange().rangeZ;
    const Vector3D<T> direction = ray.direction;
    const Point3D<T> start = ray.location;
    T _r = (T) sqrt(start.x * start.x + start.y * start.y);
    if (_r >= surface->radius && Utils::IsGettingFarFromOpticalAxis(start, direction)) // The ray is lost!
        return Ray<T, U>(start, direction, 0.0); // 0 intensity
    // Calculate propagation point at the x-range left border
    const T zleft = range.start;
    Point3D<T> prop = start + (zleft - start.z) * !direction;
    _r = (T) sqrt(prop.x * prop.x + prop.y * prop.y);
    if (_r >= surface->radius && Utils::IsGettingFarFromOpticalAxis(prop, direction)) // The ray is lost!
        return Ray<T, U>(start, direction, 0.0); // 0 intensity
    // Compute the intersection of the ray with the spherical surface
    const Vector3D<T> v = start - surface->center;
    const double vd = (double) (v | ray.direction);
    const double r = surface->curvature;
    const double _t = sqrt( (vd * vd) - ( (v | v) - (r * r) ) );
    const Point3D<T> p1 = start + (T) ( -vd - _t ) * direction;
    const Point3D<T> p2 = start + (T) ( -vd + _t ) * direction;
    const Point3D<T> p = p1.z < p2.z ? p1 : p2;
    _r = (T) sqrt(p.x * p.x + p.y * p.y);
    if (_r >= surface->radius) // The ray is lost!
        return Ray<T, U>(p, direction, 0.0); // 0 intensity
    else
        return Ray<T, U>(p, direction, ray.intensity);
}

#endif
