#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <iostream>
#include <iomanip>
#include <math.h>
#include "geometry/PrintFormat.hpp"

using namespace std;

template <typename T>
class Vector3D {
public:
    /* Members */
    const T x;
    const T y;
    const T z;
    /* Constructors */
    Vector3D(T x, T y, T z) : x(x), y(y), z(z) {
        check(x, y, z);
    }
    Vector3D(const Vector3D<T>& vector) : x(vector.x), y(vector.y), z(vector.z) {
        check(x, y, z);
    }
    /* Operators */
    const Vector3D<T> operator+(const Vector3D<T>& vector) const;
    const Vector3D<T> operator-(const Vector3D<T>& vector) const;
    const Vector3D<T> operator+=(const Vector3D<T>& vector) const;
    const Vector3D<T> operator-=(const Vector3D<T>& vector) const;
    const Vector3D<T> operator*(const Vector3D<T>& vector) const;
    const Vector3D<T> operator*(T factor) const;
    const Vector3D<T> operator*=(const Vector3D<T>& vector) const; // Vectorial product
    const T operator|(const Vector3D<T>& vector) const; // Scalar product
    const Vector3D<T> operator!() const; // Normalization operator
    const T operator~() const; // Length operator
    const bool operator==(const Vector3D<T>& vector) const;
    /* Member functions */
    const Vector3D<T> normalize() const;
    const T length() const;
    /* Friend functions */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Vector3D<U>& instance);
    template <typename U>
    friend const Vector3D<U> operator*(U factor, const Vector3D<U>& vector);
private:
    void check(T x, T y, T z);
};

template <typename T>
void Vector3D<T>::check(T x, T y, T z) {
    if ( (x != x) || (y != y) || (z != z)
      || !isfinite(x) || !isfinite(y) || !isfinite(z) )
        throw "Invalid vector!";
}

template <typename T>
const Vector3D<T> operator*(T factor, const Vector3D<T>& vector) {
return (vector * factor);
}

template <typename T>
const Vector3D<T> operator/(const Vector3D<T>& vector, T divisor) {
    return Vector3D<T>(vector.x / divisor, vector.y / divisor, vector.z / divisor);
}

template <typename T>
const Vector3D<T> Vector3D<T>::operator+(const Vector3D<T>& vector) const {
    return Vector3D<T>(*this) += vector;
}

template <typename T>
const Vector3D<T> Vector3D<T>::operator-(const Vector3D<T>& vector) const {
    return Vector3D<T>(*this) -= vector;
}

template <typename T>
const Vector3D<T> Vector3D<T>::operator*(T factor) const {
    return Vector3D<T>(factor * this->x, factor * this->y, factor * this->z);
}

template <typename T>
const Vector3D<T> Vector3D<T>::operator*(const Vector3D<T>& vector) const { // Vectorial product
    return Vector3D<T>(*this) *= vector;
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
const Vector3D<T> Vector3D<T>::operator*=(const Vector3D<T>& vector) const { // Vectorial product
    const T x = this->y * vector.z - this->z * vector.y;
    const T y = this->z * vector.x - this->x * vector.z;
    const T z = this->x * vector.y - this->y * vector.x;
    return Vector3D<T>(x, y, z);
}

template <typename T>
const T Vector3D<T>::operator|(const Vector3D<T>& vector) const { // Scalar product
    return ( this->x * vector.x + this->y * vector.y + this->z * vector.z );
}

template <typename T>
const Vector3D<T> Vector3D<T>::operator!() const { // Normalization operator
    return this->normalize();
}

template <typename T>
const T Vector3D<T>::operator~() const { // Length operator
    return this->length();
}

template <typename T>
const bool Vector3D<T>::operator==(const Vector3D<T>& vector) const {
    return ( (this->x == vector.x) && (this->y == vector.y) && (this->z == vector.z) );
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
    return out << "(" << setw(PrintFormat::width) << instance.x << "," << setw(PrintFormat::width) << instance.y << "," << setw(PrintFormat::width) << instance.z << ")";
}

#endif
