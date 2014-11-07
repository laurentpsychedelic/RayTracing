#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <iostream>

template <typename T>
class Vector3D {
public:
    const T x;
    const T y;
    const T z;
    Vector3D(T x, T y, T z) : x(x), y(y), z(z) {}
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, Vector3D<U>& instance);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, Vector3D<T>& instance) {
    return out << "Vector3D: (" << instance.x << "," << instance.y << "," << instance.z << ") @{" << &instance << "}";
}

#endif
