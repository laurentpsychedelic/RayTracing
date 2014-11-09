#ifndef MATRIX3D_HPP
#define MATRIX3D_HPP

#include <iostream>
#include <iomanip>

using namespace std;

template <typename T>
void check(T M11, T M12, T M13, T M21, T M22, T M23, T M31, T M32, T M33);

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
    /* Friend functions */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Matrix3D<U>& instance);
};

template <typename T>
void check(T M11, T M12, T M13, T M21, T M22, T M23, T M31, T M32, T M33) {
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
std::ostream& operator<<(std::ostream& out, const Matrix3D<T>& instance) {
    return out << "\n    [" << setw(4) << instance.M11 << "    " << setw(4) << instance.M12 << "    " << setw(4) << instance.M13 << "   ]" <<
                  "\n    [" << setw(4) << instance.M21 << "    " << setw(4) << instance.M22 << "    " << setw(4) << instance.M23 << "   ]" <<
                  "\n    [" << setw(4) << instance.M31 << "    " << setw(4) << instance.M32 << "    " << setw(4) << instance.M33 << "   ]";
}

#endif
