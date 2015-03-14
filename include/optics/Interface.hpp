#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "geometry/ISurface3D.hpp"
#include "geometry/SurfacePrinter.hpp"

template <typename T>
class Interface {
public:
    const double n1;
    const ISurface3D<T>& surface;
    const double n2;
public:
    /* Construtors */
    Interface(const double n1, const ISurface3D<T>& surface, const double n2) : n1(n1), surface(surface), n2(n2) {}
    /* Friend functions */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Interface<U>& instance);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Interface<T>& instance) {
    out << "{ n1: " << instance.n1 << " | surface: ";
    SurfacePrinter::print(out, &(instance.surface));
    return out << " | n2: " << instance.n2 << "}";
}

#endif
