#ifndef RANGE_HPP
#define RANGE_HPP

#include <iostream>
#include <iomanip>
#include "geometry/PrintFormat.hpp"

using namespace std;

template <typename T>
class Range {
public:
    /* Members */
    const T start;
    const T end;
    /* Constructors */
    Range(T start, T end) : start(start), end(end) {
        check(start, end);
    }
    Range(const Range<T>& range) : start(range.start), end(range.end) {
        check(start, end);
    }
    /* Operators */
    const T operator~() const; // Length operator
    const T operator&(T value) const; // Inside range
    /* Member functions */
    const T length() const;
    const bool inside(T value) const;
    /* Friend functions */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Range<U>& instance);
    template <typename U>
    friend bool operator&(U value, const Range<U>& range); // Inside range
private:
    void check(T start, T end);
};

template <typename T>
void Range<T>::check(T start, T end) {
    if ( (start != start) || (end != end) || (start > end) )
        throw "Invalid range!";
}

template <typename T>
const T Range<T>::operator~() const { // Length operator
    return this->length();
}

template <typename T>
const T Range<T>::operator&(T value) const { // Inside
    return this->inside(value);
}

template <typename T>
bool operator&(T value, const Range<T>& range) {
    return (range & value);
}

template <typename T>
const T Range<T>::length() const {
    return ( this->end - this->start );
}

template <typename T>
const bool Range<T>::inside(T value) const {
    return ( this->start <= value && value <= this-> end );
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Range<T>& instance) {
    return out << "[" << setw(PrintFormat::width) << instance.start << " ; " << setw(PrintFormat::width) << instance.end << "]";
}

#endif
