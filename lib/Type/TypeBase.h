#ifndef VERKEERSLICHT_TYPEBASE_H
#define VERKEERSLICHT_TYPEBASE_H

#include <string>

template <class T>
class TypeBase {
public:
    explicit TypeBase(int type);
    explicit TypeBase(T type);
    explicit operator int() const { return value_; }
    virtual std::string tostring();

protected:
    int value_;
};

template <class T>
std::string TypeBase<T>::tostring() {
    // Provide the implementation for the tostring() function here
    // You can return a string representation of the object or perform any other necessary operations.
    // For example:
    return std::to_string(value_);
}

template <class T>
TypeBase<T>::TypeBase(T type) {
    value_ = type;
}

template <class T>
TypeBase<T>::TypeBase(int type) {
    value_ = type;
}

#endif //VERKEERSLICHT_TYPEBASE_H
