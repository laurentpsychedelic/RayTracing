#ifndef PROPAGATORFACTORY_HPP
#define PROPAGATORFACTORY_HPP

#include "geometry/ISurface3D.hpp"
#include "geometry/SphericalSurface3D.hpp"
#include "geometry/OrthogonalPlaneSurface3D.hpp"
#include "optics/IPropagator.hpp"
#include "optics/SphericalSurfacePropagator.hpp"
#include "optics/OrthogonalPlaneSurfacePropagator.hpp"

template <typename T, typename U>
class PropagatorFactory {
public:
    static IPropagator<T, U>* GetPropagator(ISurface3D<T>* surface);
    static IPropagator<T, U>* GetPropagator(SphericalSurface3D<T>* surface);
    static IPropagator<T, U>* GetPropagator(OrthogonalPlaneSurface3D<T>* surface);
};

template <typename T, typename U>
IPropagator<T, U>* PropagatorFactory<T, U>::GetPropagator(ISurface3D<T>* surface) {
    if (dynamic_cast<SphericalSurface3D<T>* >(surface)) {
        return GetPropagator((SphericalSurface3D<T>*) surface);
    } else if (dynamic_cast<OrthogonalPlaneSurface3D<T>* >(surface)) {
        return GetPropagator((OrthogonalPlaneSurface3D<T>*) surface);
    } else return NULL;
}

template <typename T, typename U>
IPropagator<T, U>* PropagatorFactory<T, U>::GetPropagator(SphericalSurface3D<T>* surface) {
    return new SphericalSurfacePropagator<T, U>();
} 
template <typename T, typename U>
IPropagator<T, U>* PropagatorFactory<T, U>::GetPropagator(OrthogonalPlaneSurface3D<T>* surface) {
    return new OrthogonalPlaneSurfacePropagator<T, U>();
}

#endif






