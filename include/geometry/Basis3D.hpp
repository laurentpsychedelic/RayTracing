#ifndef BASIS3D_HPP
#define BASIS3D_HPP

#include "geometry/Vector3D.hpp"

template <typename T>
void check(const Vector3D<T>& u1, const Vector3D<T>& u2, const Vector3D<T>& u3);

template <typename T>
class Basis3D {
public:
    /* Members */
    const Vector3D<T> u1;
    const Vector3D<T> u2;
    const Vector3D<T> u3;
    /* Constructors */
    Basis3D<T>(const Vector3D<T>& u1, const Vector3D<T>& u2, const Vector3D<T>& u3) : u1(u1), u2(u2), u3(u3) {
        check(u1, u2, u3);
    }
    Basis3D<T>(const Basis3D<T>& basis) : u1(basis.u1), u2(basis.u2), u3(basis.u3) {
        check(u1, u2, u3);
    }
    /* Friend functions */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Basis3D<U>& instance);
};

template <typename T>
void check(const Vector3D<T>& u1, const Vector3D<T>& u2, const Vector3D<T>& u3) {
    if ( ( ~u1 == 0 ) || ( ~u2 == 0 ) || ( ~u3 == 0) // some vector is zero
      || (~(u1 * u2) == 0) || (~(u2 * u3) == 0) || (~(u3 * u3) == 0) ) { // some vector pair is made of parallel vectors
        throw "Invalid basis!";
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Basis3D<T>& instance) {
    return out << "{ " << instance.u1 << ", " << instance.u2 << ", " << instance.u3 << " }";
}

#endif
