#ifndef SINGLERAYTRACER_HPP
#define SINGLERAYTRACER_HPP

#include "optics/OpticalSystem.hpp"
#include "optics/PropagatorFactory.hpp"
#include "optics/Ray.hpp"
#include "optics/Refractor.hpp"

template <typename T, typename U>
class SingleRayTracer {
public:
    Ray<T, U> trace(const Ray<T, U>& start, const OpticalSystem<T>& optical_system);
};

template <typename T, typename U>
Ray<T, U> SingleRayTracer<T, U>::trace(const Ray<T, U>& start, const OpticalSystem<T>& optical_system) {
    const Ray<T, U> *ray = &start;
    for (auto interf : optical_system) {
        IPropagator<T, U>* propagator = PropagatorFactory<T, U>::GetPropagator(&(interf.surface));
        if (!propagator)
            throw "Null propagator!";
        Ray<T, U> inter = propagator->propagate(*ray, &(interf.surface));
        ray = &inter;
        const Vector3D<T> refracted = Refractor<T>::refract(ray->direction, interf.surface.getNormalVector(ray->location).normal, interf.n1, interf.n2);
        Ray<T, U> inter2 = Ray<T, U>(ray->location, refracted, ray->intensity);
        ray = &inter2;
    }
    return Ray<T, U>(*ray);
}

#endif
