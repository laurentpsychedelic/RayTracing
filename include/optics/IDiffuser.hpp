#ifndef IDIFFUSER_HPP
#define IDIFFUSER_HPP

#include "geometry/Vector3D.hpp"
#include "optics/Ray.hpp"
#include <vector>

template <typename T, typename U>
class IDiffuser {
public:
    /* Member functions */
    const std::vector<Ray<T, U> > diffuse(const Vector3D<T>& normal, const Ray<T, U>& incomingRay) = 0; 
    /* Vistual destructor */
    virtual ~IDiffuser();
};

#endif
