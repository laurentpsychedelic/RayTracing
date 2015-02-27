#ifndef UTILS_HPP
#define UTILS_HPP

#include "geometry/Point3D.hpp"

class Utils {
public:
    template <typename T>
    static bool IsGettingFarFromOpticalAxis(const Point3D<T>& start, const Vector3D<T>& direction);
};

template <typename T>
bool Utils::IsGettingFarFromOpticalAxis(const Point3D<T>& start, const Vector3D<T>& direction) {
    return (start | direction) > 0;
}

#endif



