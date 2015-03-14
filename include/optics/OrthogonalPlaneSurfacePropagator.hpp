#ifndef ORTHOGONALPLANESURFACEPROPAGATOR_HPP
#define ORTHOGONALPLANESURFACEPROPAGATOR_HPP

#include "geometry/OrthogonalPlaneSurface3D.hpp"
#include "geometry/Utils.hpp"
#include "optics/IPropagator.hpp"

template <typename T, typename U>
class OrthogonalPlaneSurfacePropagator : public IPropagator<T, U> {
public:
    /* Member functions */
    virtual const Ray<T, U> propagate(const Ray<T, U>& ray, const ISurface3D<T>* surface);
    /* Virtual destructor */
    virtual ~OrthogonalPlaneSurfacePropagator() {}
};

template <typename T, typename U>
const Ray<T, U> OrthogonalPlaneSurfacePropagator<T, U>::propagate(const Ray<T, U>& ray, const ISurface3D<T>* _surface) {
    if (ray.direction.z <= 0) // The ray is lost
        return Ray<T, U>(ray.location, ray.direction, 0.0); // 0 intensity
    const OrthogonalPlaneSurface3D<T>* surface = dynamic_cast<const OrthogonalPlaneSurface3D<T>* >(_surface);
    if (!surface)
        throw "Surface is not a planar surface!! (orthogonal plane surface propagator)";
    const Vector3D<T> direction = ray.direction;
    const Point3D<T> start = ray.location;
    Point3D<T> prop = start + (surface->z - start.z) * !direction;
    return Ray<T, U>(prop, direction, ray.intensity);
}

#endif
