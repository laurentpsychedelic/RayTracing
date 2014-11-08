#include <iostream>

#include "geometry/Vector3D.hpp"

using namespace std;

#define Vector Vector3D<double>

int main(int argc, char *argv[]) {
    Vector vector1(1.234, 2.345, 3.456);
    Vector vector2(1,2,3);
    cout << "v1 + v2 = " << (vector1 + vector2) << endl;
    cout << "v1 - v2 = " << (vector1 - vector2) << endl;
    cout << "v1 = " << vector1 << ", ||v1|| = " << vector1.length() << endl;
    cout << "v1/||v1|| = " << vector1.normalize() << ", ||v1/||v1|||| = " << vector1.normalize().length() << endl;
    cout << "v2 = " << vector2 << ", ||v2|| = " << vector2.length() << endl;
    cout << "v2/||v2|| = " << vector2.normalize() << ", ||v2/||v2|||| = " << vector2.normalize().length() << endl;
    return 0;
}
