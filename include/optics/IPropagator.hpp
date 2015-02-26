#ifndef IPROPAGATOR_HPP
#define IPROPAGATOR_HPP

#include "geometry/ISurface3D.hpp"
#include "optics/Ray.hpp"

template <typename T, typename U>
class IPropagator {
public:
    /* Member functions */
    virtual const Ray<T, U> propagate(const Ray<T, U>& ray, ISurface3D<T>* surface) = 0;
    /* Virtual destructor */
    virtual ~IPropagator() {}
};

#endif

