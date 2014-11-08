#include <iostream>

#include "geometry/Vector3D.hpp"

using namespace std;

#define Vector Vector3D<double>

int main(int argc, char *argv[]) {
    const Vector v1(1.234, 2.345, 3.456);
    const Vector v2(1,2,3);
    cout << "v1 = " << v1 << " , v2 = " << v2 << endl;
    cout << "v1 + v2 = " << (v1 + v2) << endl;
    cout << "v1 - v2 = " << (v1 - v2) << endl;
    cout << "v1 = " << v1 << ", ||v1|| = " << v1.length() << endl;
    cout << "v1/||v1|| = " << v1.normalize() << ", ||v1/||v1|||| = " << v1.normalize().length() << endl;
    cout << "v2 = " << v2 << ", ||v2|| = " << v2.length() << endl;
    cout << "v2/||v2|| = " << v2.normalize() << ", ||v2/||v2|||| = " << v2.normalize().length() << endl;
    const Vector u1(1, 0, 0);
    const Vector u2(0, 1, 0);
    cout << "u1 = " << u1 << " , u2 = " << u2 << endl;
    cout << "u1 * u2 = " << ( u1 * u2 ) << endl; // Vectorial product
    cout << "u1 | u2 = " << ( u1 | u2 ) << endl; // Scalar product
    return 0;
}
