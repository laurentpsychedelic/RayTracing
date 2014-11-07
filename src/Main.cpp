#include <iostream>

#include "geometry/Vector3D.hpp"

using namespace std;

#define Vector Vector3D<double>

int main(int argc, char *argv[]) {
    Vector vector(1.234, 2.345, 3.456);
    cout << vector << endl;
    return 0;
}
