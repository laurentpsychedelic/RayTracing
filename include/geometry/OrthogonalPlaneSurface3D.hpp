#ifndef ORTHOGONALPLANESURFACE3D_HPP
#define ORTHOGONALPLANESURFACE3D_HPP

#include "geometry/Point3D.hpp"
#include "geometry/LocalVector3D.hpp"
#include "geometry/ISurface3D.hpp"

template <typename T>
class OrthogonalPlaneSurface3D : public ISurface3D<T> {
public:
    virtual LocalVector3D<T> getNormalVector(const Point3D<T>& point);
    /* Members */
public:
    const T z;
public:
    /* Constructors */
    OrthogonalPlaneSurface3D(const T z) : z(z) {
        check(z);
    }
    /* Friend functions */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const OrthogonalPlaneSurface3D<U>& instance);
private:
    void check(const T z);
};

template <typename T>
LocalVector3D<T> OrthogonalPlaneSurface3D<T>::getNormalVector(const Point3D<T>& point) {
    return LocalVector3D<T>(Point3D<T>(point.x, point.y, z), Vector3D<T>(0.0, 0.0, -1.0));
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const OrthogonalPlaneSurface3D<T>& instance) {
    return out << "{z: " << instance.z << "}";
}

template <typename T>
void OrthogonalPlaneSurface3D<T>::check(const T z) {
    if (z != z)
        throw "Invalid \"z\" position for orthogonal plane surface!";
}

#endif

