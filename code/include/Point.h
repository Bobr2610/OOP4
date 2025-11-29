#ifndef POINT_H
#define POINT_H

#include <memory>
#include <concepts>
#include <iostream>

template<typename T>
concept ScalarType = std::is_arithmetic_v<T>;

template<ScalarType T>
class Point {
private:
    T x_, y_;

public:
    Point() : x_(0), y_(0) {}
    Point(T x, T y) : x_(x), y_(y) {}
    
    T getX() const { return x_; }
    T getY() const { return y_; }
    void setX(T x) { x_ = x; }
    void setY(T y) { y_ = y; }
    
    Point operator+(const Point& other) const {
        return Point(x_ + other.x_, y_ + other.y_);
    }
    
    Point operator-(const Point& other) const {
        return Point(x_ - other.x_, y_ - other.y_);
    }
    
    Point operator*(T scalar) const {
        return Point(x_ * scalar, y_ * scalar);
    }
    
    Point operator/(T scalar) const {
        return Point(x_ / scalar, y_ / scalar);
    }
    
    bool operator==(const Point& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x_ << ", " << p.y_ << ")";
        return os;
    }
};

#endif

