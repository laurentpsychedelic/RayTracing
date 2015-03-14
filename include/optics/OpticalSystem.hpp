#ifndef OPTICALSYSTEM_HPP
#define OPTICALSYSTEM_HPP

#include "optics/Interface.hpp"
#include <vector>
using namespace std;

template <typename T>
class OpticalSystem : public vector<Interface<T> > {
public:
    /* Friend functions */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const OpticalSystem<U>& instance);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const OpticalSystem<T>& instance) {
    out << "[[ \n";
    for (auto interf : instance) {
        out << "    " << interf << endl;
    }
    out << "]]";
    return out;
}

#endif
