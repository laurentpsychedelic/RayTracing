#ifndef SURFACEPRINTER_HPP
#define SURFACEPRINTER_HPP

#include "geometry/ISurface3D.hpp"
#include "geometry/SphericalSurface3D.hpp"
#include "geometry/OrthogonalPlaneSurface3D.hpp"
#include <iostream>

template <typename T>
class ISurface3D;

class SurfacePrinter {
public:
    template <typename T>
    static std::ostream& print(std::ostream& out, const ISurface3D<T>* surface);
};

template <typename T>
std::ostream& SurfacePrinter::print(std::ostream& out, const ISurface3D<T>* surface) {
    if (dynamic_cast<const SphericalSurface3D<T>* >(surface)) {
        return out << *((const SphericalSurface3D<T>*) surface);
    } else if (dynamic_cast<const OrthogonalPlaneSurface3D<T>* >(surface)) {
        return out << *((const OrthogonalPlaneSurface3D<T>*) surface);
    } else return out << "????";
}

#endif
