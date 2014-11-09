#ifndef TRANSFORMATIONMATRIX3D_HPP
#define TRANSFORMATIONMATRIX3D_HPP

#include "geometry/Basis3D.hpp"
#include "geometry/Matrix3D.hpp"

template <typename T>
class TransformationMatrix3D : public Matrix3D<T> {
public:
    TransformationMatrix3D<T>(const Basis3D<T>& basis1, const Basis3D<T>& basis2) : Matrix3D<T>(buildTransformationMatrixFromBases(basis1, basis2)) { }
    TransformationMatrix3D<T>(T M11, T M12, T M13, T M21, T M22, T M23, T M31, T M32, T M33) : Matrix3D<T>(M11, M12, M13, M21, M22, M23, M31, M32, M33) { }
    template <typename U>
    friend Matrix3D<U> buildTransformationMatrixFromBases(const Basis3D<U>& basis1, const Basis3D<U>& basis2);
};

/**
 * Given the coordinates of two bases (in an arbitrary coordinate system),
 * this function compute the matrix that is to be applied to the coordinates of a point
 * in the second basis to get the coordinates of the same point in the first basis
 */
template <typename T>
Matrix3D<T> buildTransformationMatrixFromBases(const Basis3D<T>& basis1, const Basis3D<T>& basis2) {
    const Vector3D<T> xs1(basis1.u1.x, basis1.u2.x, basis1.u3.x);
    const Vector3D<T> ys1(basis1.u1.y, basis1.u2.y, basis1.u3.y);
    const Vector3D<T> zs1(basis1.u1.z, basis1.u2.z, basis1.u3.z);
    const Vector3D<T> xs2(basis2.u1.x, basis2.u2.x, basis2.u3.x);
    const Vector3D<T> ys2(basis2.u1.y, basis2.u2.y, basis2.u3.y);
    const Vector3D<T> zs2(basis2.u1.z, basis2.u2.z, basis2.u3.z);

    const Matrix3D<T> A(basis1.u1.x, basis1.u1.y, basis1.u1.z,
                        basis1.u2.x, basis1.u2.y, basis1.u2.z,
                        basis1.u3.x, basis1.u3.y, basis1.u3.z);
    const T det = ~A;
    const T M11 = basis2.u1 | (ys1 * zs1);
    const T M12 = basis2.u1 | (zs1 * xs1);
    const T M13 = basis2.u1 | (xs1 * ys1);
    const T M21 = basis2.u2 | (ys1 * zs1);
    const T M22 = basis2.u2 | (zs1 * xs1);
    const T M23 = basis2.u2 | (xs1 * ys1);
    const T M31 = basis2.u3 | (ys1 * zs1);
    const T M32 = basis2.u3 | (zs1 * xs1);
    const T M33 = basis2.u3 | (xs1 * ys1);

    return Matrix3D<T>(M11, M12, M13, M21, M22, M23, M31, M32, M33) / det;
}

#endif
