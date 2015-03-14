#ifndef REFRACTOR_HPP
#define REFRACTOR_HPP

#include <math.h>
#include "geometry/Basis3D.hpp"
#include "geometry/Vector3D.hpp"
#include "geometry/TransformationMatrix3D.hpp"

template <typename T>
class Refractor {
public:
    static Vector3D<T> refract(const Vector3D<T>& incident, const Vector3D<T>& normal, double n1, double n2);
};

template <typename T>
Vector3D<T> Refractor<T>::refract(const Vector3D<T>& _incident, const Vector3D<T>& _normal, double n1, double n2) {
    Vector3D<T> incident = !_incident;
    Vector3D<T> normal = !_normal;
    if ( (n1 != n1) || (!isfinite(n1))
      || (n2 != n2) || (!isfinite(n2)) )
        throw "Bad refractive index!";
    if ( (~(incident * normal) == 0)   // incident ray is parallel to the normal vector
      || ( (incident | normal) == 0) ) // incident ray is perpendicular to the normal vector
        return incident; // No refraction, straight propagation
    // Compute a local basis
    const Vector3D<T> w = !(normal);
    const Vector3D<T> v = !(incident * normal);
    const Vector3D<T> u = !(v * w);
    const Basis3D<T> local_basis(u, v, w);
    // Compute the coordinates of the incident vector
    const T x1 = incident | u;
    // const T y1 = 0; // incident | v = 0 !!
    const T z1 = incident | w;

    // Compute the coordinates of the refracted vector
    T x2;
    T z2;
    const T x2_tmp = (n1 / n2) * x1;
    if (x2_tmp > 1 || x2_tmp < -1) { // Total reflection!
        x2 =  x1;
        z2 = -z1;
    } else {
        x2 = x2_tmp;
        z2 = copysign( sqrt(1 - x2 * x2), z1);
    }

    // Compute coordinate transform to get the coordinates in the original basis
    const Basis3D<T> orig(Vector3D<T>(1, 0, 0), Vector3D<T>(0, 1, 0), Vector3D<T>(0, 0, 1));
    const Basis3D<T> targ(u, v, w);
    const Matrix3D<T> M = (TransformationMatrix3D<T>(targ, orig))^-1;
    // Compute the coordinates of the refracted vector in the original basis
    return !(M * Vector3D<T>(x2, 0, z2));
}

#endif
