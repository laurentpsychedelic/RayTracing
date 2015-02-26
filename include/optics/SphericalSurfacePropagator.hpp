#ifndef SPHERICALSURFACEPROPAGATOR_HPP
#define SPHERICALSURFACEPROPAGATOR_HPP

#include "geometry/SphericalSurface3D.hpp"
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
    const SphericalSurface3D<T>* surface = dynamic_cast<SphericalSurface3D<T>* >(_surface);
    if (!surface)
        throw "Surface is not a spherical surface!! (spherical surface propagator)";
    throw "Not yet implemented!";
}

#endif


