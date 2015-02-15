#ifndef IMAGEDIFFUSER_HPP
#define IMAGEDIFFUSER_HPP

#include <math.h>
#include <iostream>
#include <iomanip>
#include "geometry/PrintFormat.hpp"
#include "geometry/Vector3D.hpp"
#include "optics/Ray.hpp"

#define PI 3.14 // <- fix-me!!

template <typename T, typename U>
class ObjectDiffuser {
public:
    /* members */
    const double diffusionAngle;
    /* Member functions */
    const std::vector<Ray<T, U> > diffuse(const Vector3D<T>& normal, const Ray<T, U>& incomingRay) const; 
    /* Constructors */
    ObjectDiffuser(const double diffusionAngle): diffusionAngle(diffusionAngle) {
        check(diffusionAngle);
    }
    /* Friend functions */
    template <typename V, typename W>
    friend std::ostream& operator<<(std::ostream& out, const ObjectDiffuser<V, W>& instance);
private:
    void check(const double diffusionAngle);
};

template <typename T, typename U>
void ObjectDiffuser<T,U>::check(const double diffusionAngle) {
    if (diffusionAngle < 0 || diffusionAngle > PI || diffusionAngle != diffusionAngle)
        throw "Bad diffusion angle!";
}

template <typename T, typename U>
const std::vector<Ray<T, U> > ObjectDiffuser<T, U>::diffuse(const Vector3D<T>& normal, const Ray<T, U>& incomingRay) const {
    throw "No yet implemented!";
} 

template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const ObjectDiffuser<T, U>& instance) {
    return out << "{ angle range = [ 0 ; " << setw(PrintFormat::width) << instance.diffusionAngle << " ] }";
}

#endif
