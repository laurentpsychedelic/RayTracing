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
    double stepDiffusionAngle = PI / 50.0f;
    double stepAzimuth = PI / 50.0f;
    std::vector<Ray<T, U> > rays;
    U nominalIntensity = (U) ( incomingRay.intensity / (double) ( 100.0 * (int) ( diffusionAngle / stepDiffusionAngle ) + 1 ) );
    rays.push_back(Ray<T, U>(incomingRay.location, normal, nominalIntensity));


    const double normal_azimuth = atan2(normal.y, normal.x);
    const double normal_angle = atan2(normal.z, sqrt(normal.x * normal.x + normal.y * normal.y));

    for (double _diffusionAngle = stepDiffusionAngle; _diffusionAngle < diffusionAngle; _diffusionAngle += stepDiffusionAngle) {
        for (double _azimuth = 0; _azimuth < 2 * PI; _azimuth += stepAzimuth) {
            const double x = cos(_azimuth) * sin(_diffusionAngle);
            const double y = sin(_azimuth) * sin(_diffusionAngle);
            const double z = cos(_diffusionAngle);
            // rotate raw ray according to the normal direction
            Matrix3D<T> R(0, 0, 0, 0, 0, 0, 0, 0, 0); // rotation of angle (normal_angle) around equatorial axis at azimuth (normal_azimuth) [[ (x, y) = ( cos(normal_azimuth), sin(normal_azimuth) ) ]]
            throw "Diffused ray rotation according to normal vector not implemented!";
            rays.push_back(Ray<T, U>(incomingRay.location, R * Vector3D<T>(x, y, z), nominalIntensity));
        }
    }
    return rays;
} 

template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const ObjectDiffuser<T, U>& instance) {
    return out << "{ angle range = [ 0 ; " << setw(PrintFormat::width) << instance.diffusionAngle << " ] }";
}

#endif
