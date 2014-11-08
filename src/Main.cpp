#include <iostream>

#include "geometry/Basis3D.hpp"
#include "geometry/Vector3D.hpp"

using namespace std;

#define Vector Vector3D<double>
#define Basis Basis3D<double>

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
        const Basis b1(u1, u2, u3);
        cout << "{b1} = " << b1 << endl;
        const Basis b2(u1, u1 * 2, u1 / 2.3);
        cout << "{b2} = " << b2 << endl;
        const Vector v(2.0 / 0.0, 0, sqrt(-1));
        const Basis b3(u1, u2, v);
        cout << "{b3} = " << b3 << endl;
    } catch (const char* error) {
        cout << "ERROR! >> " << error << endl;
        return -1;
    }
    return 0;
}
