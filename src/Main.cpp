#include <iostream>

#include "geometry/Basis3D.hpp"
#include "geometry/Matrix3D.hpp"
#include "geometry/TransformationMatrix3D.hpp"
#include "geometry/Vector3D.hpp"
#include "optics/Refractor.hpp"

using namespace std;

#define Basis Basis3D<double>
#define Matrix Matrix3D<double>
#define Refractor Refractor<double>
#define TransformationMatrix TransformationMatrix3D<double>
#define Vector Vector3D<double>

int main(int argc, char *argv[]) {
    try {
        const Vector v1(1.234, 2.345, 3.456);
        const Vector v2(1,2,3);
        cout << "v1 = " << v1 << " , v2 = " << v2 << endl;
        cout << "v1 + v2 = " << (v1 + v2) << endl;
        cout << "v1 - v2 = " << (v1 - v2) << endl;
        cout << "v1 = " << v1 << ", ||v1|| = " << ~v1 << endl;
        cout << "v1/||v1|| = " << !v1 << ", ||v1/||v1|||| = " << ~!v1 << endl;
        cout << "v2 = " << v2 << ", ||v2|| = " << ~v2 << endl;
        cout << "v2/||v2|| = " << !v2 << ", ||v2/||v2|||| = " << ~!v2 << endl;
        const Vector u1(1, 0, 0);
        const Vector u2(0, 1, 0);
        cout << "u1 = " << u1 << " , u2 = " << u2 << endl;
        cout << "u1 * u2 = " << ( u1 * u2 ) << endl; // Vectorial product
        cout << "u1 | u2 = " << ( u1 | u2 ) << endl; // Scalar product
        const Vector u3 = u1 * u2;
        cout << "u3 = " << u3 << endl;
        cout << "2.0 * u1 + u2 * 1.5 - u3 * 4.0 = " << (2.0 * u1 + u2 / 2.0 - u3 * 4.0) << endl;
        const Matrix m(1, 0, 0, 0, 1, 0, 0, 0, 1);
        cout << "2 * [M] / 3 = " << (2.0 * m / 3.0) << endl;
        const Matrix m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
        cout << "[M1] = " << m1 << endl;
        const Matrix m2(8, 1, 7, 2, 6, 3, 5, 4, 0);
        cout << "[M2] = " << m2 << endl;
        cout << "[M1 + M2] = " << (m1 + m2) << endl;
        cout << "[M1 * M2] = " << (m1 * m2) << endl;
        cout << "[M2 * M1] = " << (m2 * m1) << endl;
        cout << "[M * M1] = " << (m * m1) << endl;
        const Matrix m3(7, 2, 1, 0, 3, -1, -3, 4, -2);
        cout << "[M3] = " << m3 << endl;
        cout << "[M3^-1] = " << (m3^-1) << endl;
        const Matrix im3(-2, 8, -5, 3, -11, 7, 9, -34, 21);
        cout << "[IM3] = " << im3 << endl;
        cout << "[M3^-1]==[IM3] ? -> " << ((m3^-1) == im3 ? "yes" : "no") << endl;
        const Basis b1(u1, u2, u3);
        cout << "{b1} = " << b1 << endl;
        const Basis b2(2.0 * u2, 0.5 * u3, u1 / 10.0);
        cout << "{b2} = " << b2 << endl;
        const TransformationMatrix t(b1, b2);
        cout << "[T] = " << t << endl;
        const Vector v(1, 1, 1);
        cout << "v = " << v << endl;
        cout << "[T] * v = " << (t * v) << endl;

        const Vector normal = !Vector(0, 0, 1);
        const Vector incident = !Vector(sqrt(2), 0, -sqrt(2));
        const double n1 = 1.0; // Air
        const double n2 = 1.333; // Water
        const Vector refracted = Refractor::refract(incident, normal, n1, n2);
        cout << "inc = " << incident << endl;
        cout << "ref = " << refracted << endl;
    } catch (const char* error) {
        cout << "ERROR! >> " << error << endl;
        return -1;
    }
    return 0;
}
