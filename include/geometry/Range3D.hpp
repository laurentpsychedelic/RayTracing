#ifndef RANGE3D_HPP
#define RANGE3D_HPP

#include <iostream>
#include "geometry/Point3D.hpp"
#include "geometry/Range.hpp"

template <typename T>
class Range3D {
public:
    /* Members */
    const Range<T> rangeX;
    const Range<T> rangeY;
    const Range<T> rangeZ;
    /* Constructors */
    Range3D(const Range<T>& rangeX, const Range<T>& rangeY, const Range<T>& rangeZ) : rangeX(rangeX), rangeY(rangeY), rangeZ(rangeZ) {
        check(rangeX, rangeY, rangeZ);
    }
    Range3D(const Range3D<T>& range3D) : rangeX(range3D.rangeX), rangeY(range3D.rangeY), rangeZ(range3D.rangeZ) {
        check(rangeX, rangeY, rangeZ);
    }
    /* Operators */
    const T operator&(const Point3D<T>& point) const; // Inside range
    /* Member functions */
    const bool inside(const Point3D<T>& point) const;
    /* Friend functions */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Range3D<U>& instance);
    template <typename U>
    friend bool operator&(const Point3D<T>& point, const Range<U>& range); // Inside range
private:
    void check(const Range<T>& rangeX, const Range<T>& rangeY, const Range<T>& rangeZ);
};

template <typename T>
void Range3D<T>::check(const Range<T>& rangeX, const Range<T>& rangeY, const Range<T>& rangeZ) {
    /* NOTHING */
}

template <typename T>
const T Range3D<T>::operator&(const Point3D<T>& point) const { // Inside
    return this->inside(point);
}

template <typename T>
const bool operator&(const Point3D<T>& point, const Range<T>& range) {
    return (range & point);
}

template <typename T>
const bool Range3D<T>::inside(const Point3D<T>& point) const {
    return ( (rangeX & point.x) && (rangeY & point.y) && (rangeZ & point.z) );
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Range3D<T>& instance) {
    return out << "{ x:" << instance.rangeX << ", y:" << instance.rangeY << ", z:" << instance.rangeZ << "}";
}


#endif
