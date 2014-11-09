#ifndef MATRIX3D_HPP
#define MATRIX3D_HPP

#include <iostream>
#include <iomanip>
#include "geometry/Vector3D.hpp"
#include "geometry/PrintFormat.hpp"

using namespace std;

template <typename T>
class Matrix3D {
public:
    /* Members */
    const T M11;
    const T M12;
    const T M13;
    const T M21;
    const T M22;
    const T M23;
    const T M31;
    const T M32;
    const T M33;
    /* Contructors */
    Matrix3D(T M11, T M12, T M13, T M21, T M22, T M23, T M31, T M32, T M33) : M11(M11), M12(M12), M13(M13), M21(M21), M22(M22), M23(M23), M31(M31), M32(M32), M33(M33) {
        check(M11, M12, M13, M21, M22, M23, M31, M32, M33);
    }
    Matrix3D(const Matrix3D<T>& matrix) : M11(matrix.M11), M12(matrix.M12), M13(matrix.M13), M21(matrix.M21), M22(matrix.M22), M23(matrix.M23), M31(matrix.M31), M32(matrix.M32), M33(matrix.M33) {
        check(M11, M12, M13, M21, M22, M23, M31, M32, M33);
    }
    /* Operators */
    const Matrix3D<T> operator+(const Matrix3D<T>& matrix) const;
    const Matrix3D<T> operator*(T factor) const;
    const Matrix3D<T> operator*(const Matrix3D<T>& matrix) const;
    const Matrix3D<T> operator/(T divisor) const;
    /* Friend functions */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Matrix3D<U>& instance);
    template <typename U>
    friend const Matrix3D<U> operator*(U factor, const Matrix3D<U>& vector);
private:
    void check(T M11, T M12, T M13, T M21, T M22, T M23, T M31, T M32, T M33);
};

template <typename T>
void Matrix3D<T>::check(T M11, T M12, T M13, T M21, T M22, T M23, T M31, T M32, T M33) {
    if ( ( M11 != M11 || !isfinite(M11) )
      || ( M12 != M12 || !isfinite(M12) )
      || ( M13 != M13 || !isfinite(M13) )
      || ( M21 != M21 || !isfinite(M21) )
      || ( M22 != M22 || !isfinite(M22) )
      || ( M23 != M23 || !isfinite(M23) )
      || ( M31 != M31 || !isfinite(M31) )
      || ( M32 != M32 || !isfinite(M32) )
      || ( M33 != M33 || !isfinite(M33) ) )
        throw "Invalid matrix!";
}
template <typename T>
const Matrix3D<T> Matrix3D<T>::operator+(const Matrix3D<T>& matrix) const {
    return Matrix3D<T>(this->M11 + matrix.M11, this->M12 + matrix.M12, this->M13 + matrix.M13,
                       this->M21 + matrix.M21, this->M22 + matrix.M22, this->M23 + matrix.M23,
                       this->M31 + matrix.M31, this->M32 + matrix.M32, this->M33 + matrix.M33);
}

template <typename T>
const Matrix3D<T> Matrix3D<T>::operator*(T factor) const {
    return Matrix3D<T>(factor * this->M11, factor * this->M12, factor * this->M13,
                       factor * this->M21, factor * this->M22, factor * this->M23,
                       factor * this->M31, factor * this->M32, factor * this->M33);
}

template <typename T>
const Matrix3D<T> Matrix3D<T>::operator*(const Matrix3D<T>& matrix) const {
    const Vector3D<T> row1(this->M11, this->M12, this->M13);
    const Vector3D<T> row2(this->M21, this->M22, this->M23);
    const Vector3D<T> row3(this->M31, this->M32, this->M33);
    const Vector3D<T> col1(matrix.M11, matrix.M21, matrix.M31);
    const Vector3D<T> col2(matrix.M12, matrix.M22, matrix.M32);
    const Vector3D<T> col3(matrix.M13, matrix.M23, matrix.M33);
    return Matrix3D<T>(row1 | col1, row1 | col2, row1 | col3,
                       row2 | col1, row2 | col2, row2 | col3,
                       row3 | col1, row3 | col2, row3 | col3);
}

template <typename T>
const Matrix3D<T> operator*(T factor, const Matrix3D<T>& matrix) {
    return (matrix * factor);
}

template <typename T>
const Matrix3D<T> Matrix3D<T>::operator/(T divisor) const {
    return Matrix3D<T>(this->M11 / divisor, this->M12 / divisor, this->M13 / divisor,
                       this->M21 / divisor, this->M22 / divisor, this->M23 / divisor,
                       this->M31 / divisor, this->M32 / divisor, this->M33 / divisor);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix3D<T>& instance) {
    return out << "\n    [" << setw(PrintFormat::width) << instance.M11 << "    " << setw(PrintFormat::width) << instance.M12 << "    " << setw(PrintFormat::width) << instance.M13 << "]" <<
                  "\n    [" << setw(PrintFormat::width) << instance.M21 << "    " << setw(PrintFormat::width) << instance.M22 << "    " << setw(PrintFormat::width) << instance.M23 << "]" <<
                  "\n    [" << setw(PrintFormat::width) << instance.M31 << "    " << setw(PrintFormat::width) << instance.M32 << "    " << setw(PrintFormat::width) << instance.M33 << "]";
}

#endif
