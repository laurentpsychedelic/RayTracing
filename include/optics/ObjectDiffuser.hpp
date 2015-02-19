#ifndef IMAGEDIFFUSER_HPP
#define IMAGEDIFFUSER_HPP

#define _USE_MATH_DEFINES
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <iostream>
#include <iomanip>
#include "geometry/PrintFormat.hpp"
#include "geometry/Vector3D.hpp"
#include "optics/Ray.hpp"

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
    if (diffusionAngle < 0 || diffusionAngle > M_PI || diffusionAngle != diffusionAngle)
        throw "Bad diffusion angle!";
}

template <typename T, typename U>
const std::vector<Ray<T, U> > ObjectDiffuser<T, U>::diffuse(const Vector3D<T>& _normal, const Ray<T, U>& incomingRay) const {
    const Vector3D<T> normal = !_normal;
    double stepDiffusionAngle = M_PI / 50.0f;
    double stepAzimuth = M_PI / 50.0f;
    std::vector<Ray<T, U> > rays;
    U nominalIntensity = (U) ( incomingRay.intensity / (double) ( 100.0 * (int) ( diffusionAngle / stepDiffusionAngle ) + 1 ) );
    rays.push_back(Ray<T, U>(incomingRay.location, normal, nominalIntensity));


    const double normal_angle = atan2(sqrt(normal.x * normal.x + normal.y * normal.y), normal.z);
    std::cout << normal_angle << "..." << std::endl;
    const double _cos = cos(normal_angle);
    const double _sin = sin(normal_angle);
    const double ux = -normal.y;
    const double uy =  normal.z;
    const Matrix3D<T> R( _cos + ux * ux * ( 1 - _cos), ux * uy * (1 - _cos)       ,  uy * _sin,
                   uy * ux * (1 - _cos)        , _cos + uy * uy * (1 - _cos), -ux * _sin,
                  -uy * _sin                   , ux * _sin                  , _cos      );
    for (double _diffusionAngle = stepDiffusionAngle; _diffusionAngle < diffusionAngle; _diffusionAngle += stepDiffusionAngle) {
        for (double _azimuth = 0; _azimuth < 2 * M_PI; _azimuth += stepAzimuth) {
            const double x = cos(_azimuth) * sin(_diffusionAngle);
            const double y = sin(_azimuth) * sin(_diffusionAngle);
            const double z = cos(_diffusionAngle);
            // rotate raw ray according to the normal direction
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
