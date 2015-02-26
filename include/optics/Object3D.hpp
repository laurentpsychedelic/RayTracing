#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "optics/PointSource3D.hpp"

template <typename T, typename U>
class Object3D : public vector<PointSource3D<T, U> > {
};

#endif
