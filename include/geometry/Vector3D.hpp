#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <iostream>
#include <math.h>

template <typename T>
class Vector3D {
public:
    /* Members */
    const T x;
    const T y;
    const T z;
    /* Constructors */
    Vector3D(T x, T y, T z) : x(x), y(y), z(z) {}
    Vector3D(const Vector3D<T>& vector) : x(vector.x), y(vector.y), z(vector.z) {}
    /* Operators */
    const Vector3D<T> operator+(const Vector3D<T>& vector) const;
    const Vector3D<T> operator-(const Vector3D<T>& vector) const;
    const Vector3D<T> operator+=(const Vector3D<T>& vector) const;
    const Vector3D<T> operator-=(const Vector3D<T>& vector) const;
    /* Member functions */
    const Vector3D<T> normalize() const;
    const T length() const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Vector3D<U>& instance);
};

template <typename T>
const Vector3D<T> Vector3D<T>::operator+(const Vector3D<T>& vector) const {
    return Vector3D<T>(*this) += vector;
}

template <typename T>
const Vector3D<T> Vector3D<T>::operator-(const Vector3D<T>& vector) const {
    return Vector3D<T>(*this) -= vector;
}

template <typename T>
const Vector3D<T> Vector3D<T>::operator+=(const Vector3D<T>& vector) const {
    const T x = this->x + vector.x;
    const T y = this->y + vector.y;
    const T z = this->z + vector.z;
    return Vector3D<T>(x, y, z);
}

template <typename T>
const Vector3D<T> Vector3D<T>::operator-=(const Vector3D<T>& vector) const {
    const T x = this->x - vector.x;
    const T y = this->y - vector.y;
    const T z = this->z - vector.z;
    return Vector3D<T>(x, y, z);
}

template <typename T>
const Vector3D<T> Vector3D<T>::normalize() const {
    const T l = length();
    return Vector3D<T>(this->x / l, this->y / l, this->z / l);
}

template <typename T>
const T Vector3D<T>::length() const {
    const T x = this->x;
    const T y = this->y;
    const T z = this->z;
    return sqrt( x * x + y * y + z * z );
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector3D<T>& instance) {
    return out << "(" << instance.x << "," << instance.y << "," << instance.z << ")";
}


#endif
