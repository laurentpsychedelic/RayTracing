#ifndef GRIDSURFACE_HPP
#define GRIDSURFACE_HPP

#include <limits>
#include "geometry/Point3D.hpp"
#include "geometry/ISurface3D.hpp"

using namespace std;

template <typename T>
class GridSurface3D : ISurface3D<T> {
public:
    virtual Range3D<T> getRange();
    virtual bool intersects(const Point3D<T>& point);    
    virtual LocalVector3D<T> getLocalVector(const Point3D<T>& point);
    /* Members */
private:
    T* dataZ; // []
    Range3D<T>* range;
    T stepX;
    T stepY;
    int Nx = 0;
    int Ny = 0;
public:
    /* Constructors */
    GridSurface3D(const Range<T>& rangeX, T stepX, const Range<T>& rangeY, T stepY, const T dataZ []);
    /* Destructor */
    ~GridSurface3D();
    /* Friend functions */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const GridSurface3D<U>& instance);
};

template <typename T>
GridSurface3D<T>::GridSurface3D(const Range<T>& rangeX, T stepX, const Range<T>& rangeY, T stepY, const T dataZ []) : stepX(stepX), stepY(stepY) {
    Nx = ( ~rangeX / stepX ) + 1;
    Ny = ( ~rangeY / stepY ) + 1;
    const int length = Nx * Ny;
    this->dataZ = new T[length];
    T minZ = numeric_limits<T>::max();
    T maxZ = numeric_limits<T>::min();
    for (int i = 0; i < length; ++i) {
        const T Zvalue = dataZ[i];
        if (Zvalue < minZ)
            minZ = Zvalue;
        if (Zvalue > maxZ)
            maxZ = Zvalue;
        this->dataZ[i] = Zvalue;
    }
    this->range = new Range3D<T>(rangeX, rangeY, Range<T>(minZ, maxZ));
}

template <typename T>
GridSurface3D<T>::~GridSurface3D() {
    delete [] this->dataZ;
    delete [] range;
}


template <typename T>
Range3D<T> GridSurface3D<T>::getRange() {
    return Range3D<T>(*(this->range));
}

template <typename T>
bool GridSurface3D<T>::intersects(const Point3D<T>& point) {
    if (! ( (*range) & point ) )
        return false;
    const Range<T> rangeX = range->rangeX;
    const Range<T> rangeY = range->rangeY;
    const T x = point.x;
    const T y = point.y;
    const T z = point.z;
    const int x1 = (int) ( (x - rangeX.start) / this->stepX );
    const int x2 = x1 + 1;
    const int y1 = (int) ( (y - rangeY.start) / this->stepY );
    const int y2 = y1 + 1;
    if ( (x == x1 || x == x2) && (y == y1 || y == y2) )
        return true;
    const T z11 = this->dataZ[x1 + y1 * Nx];
    const T z12 = this->dataZ[x1 + y2 * Nx];
    const T z21 = this->dataZ[x2 + y1 * Nx];
    const T z22 = this->dataZ[x2 + y2 * Nx];
    return ( ( z >= z11 || z >= z12 || z >= z21 || z >= z22 )
             && ( z <= z11 || z <= z12 || z <= z21 || z <= z22 ));
}

template <typename T>
LocalVector3D<T> GridSurface3D<T>::getLocalVector(const Point3D<T>& point) {
    if (! ( (*range) & point ) )
        throw "Outside range!";
    const Range<T> rangeX = range->rangeX;
    const Range<T> rangeY = range->rangeY;
    const T x = point.x;
    const T y = point.y;
    // const T z = point.z;
    const int x1 = (int) ( (x - rangeX.start) / this->stepX );
    const int x2 = x1 + 1;
    const int y1 = (int) ( (y - rangeY.start) / this->stepY );
    const int y2 = y1 + 1;
    const T z11 = this->dataZ[x1 + y1 * Nx];
    const T z12 = this->dataZ[x1 + y2 * Nx];
    const T z21 = this->dataZ[x2 + y1 * Nx];
    const T z22 = this->dataZ[x2 + y2 * Nx];
    const Vector3D<T> t12(x2 - x1, y1, z21 - z11);
    const Vector3D<T> t22(x2 - x1, y2, z22 - z12);
    const Vector3D<T> t11(x1, y2 - y1, z12 - z11);
    const Vector3D<T> t21(x2, y2 - y1, z22 - z21);
    return LocalVector3D<T>(point, !( (t12 * t11) + (t22 * t21) ));
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const GridSurface3D<T>& instance) {
    return out << "[[ Range: " << *(instance.range) << " ; data @ " << instance.dataZ << " ]]";
}

#endif
