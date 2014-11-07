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
    Vector3D(Vector3D<U>& vector) : x(vector.x), y(vector.y), z(vector.z) {}

    template <typename U>
    const Vector3D<U> operator+(Vector3D<U>& vector) const;

    template <typename U>
    const Vector3D<U> operator+=(Vector3D<U>& vector) const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Vector3D<U>& instance);
};

template <typename T>
template <typename U>
const Vector3D<U> Vector3D<T>::operator+(Vector3D<U>& vector) const {
    return Vector3D<U>(*this) += vector;
}

template <typename T>
template <typename U>
const Vector3D<U> Vector3D<T>::operator+=(Vector3D<U>& vector) const {
    const U x = this->x + vector.x;
    const U y = this->y + vector.y;
    const U z = this->z + vector.z;
    return Vector3D<U>(x, y, z);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector3D<T>& instance) {
    return out << "Vector3D: (" << instance.x << "," << instance.y << "," << instance.z << ") @{" << &instance << "}";
}

#endif
