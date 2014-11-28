#ifndef LOCALVECTOR_HPP
#define LOCALVECTOR_HPP

#include "geometry/Point3D.hpp"
#include "geometry/Vector3D.hpp"
#include <iostream>

template <typename T>
class LocalVector3D
{
public:
    /* Members */
    const Point3D<T> location;
    const Vector3D<T> normal;
    /* Constructors */
    LocalVector3D(const Point3D<T>& location, const Vector3D<T>& normal) : location(location), normal(normal) {
        check(location, normal);
    }
    LocalVector3D(const LocalVector3D<T>& vector) : location(vector.location), normal(vector.normal) {
        check(location, normal);
    }
private:
    void check(const Point3D<T>& location, const Vector3D<T>& normal);
    /* Friend functions */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const LocalVector3D<U>& instance);
};

template <typename T>
void LocalVector3D<T>::check(const Point3D<T>& location, const Vector3D<T>& normal) {
    /* NOTHING */
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const LocalVector3D<T>& instance) {
    return out << "<< Local vector: location=" << instance.location << " ; normal=" << instance.normal << " >>";
}

#endif
