#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Figure.h"
#include <cmath>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

template<ScalarType T>
class Triangle : public Figure<T> {
public:
    Triangle(const Point<T>& center, T radius) {
        T angle1 = 0;
        T angle2 = 2 * M_PI / 3;
        T angle3 = 4 * M_PI / 3;
        
        this->vertices_.push_back(std::make_unique<Point<T>>(
            center.getX() + radius * std::cos(angle1),
            center.getY() + radius * std::sin(angle1)
        ));
        this->vertices_.push_back(std::make_unique<Point<T>>(
            center.getX() + radius * std::cos(angle2),
            center.getY() + radius * std::sin(angle2)
        ));
        this->vertices_.push_back(std::make_unique<Point<T>>(
            center.getX() + radius * std::cos(angle3),
            center.getY() + radius * std::sin(angle3)
        ));
    }
    
    Triangle(const Point<T>& v1, const Point<T>& v2, const Point<T>& v3) {
        this->vertices_.push_back(std::make_unique<Point<T>>(v1));
        this->vertices_.push_back(std::make_unique<Point<T>>(v2));
        this->vertices_.push_back(std::make_unique<Point<T>>(v3));
    }
    
    Triangle(const Triangle& other) : Figure<T>(other) {}
    Triangle& operator=(const Triangle& other) {
        Figure<T>::operator=(other);
        return *this;
    }
    Triangle(Triangle&& other) noexcept : Figure<T>(std::move(other)) {}
    Triangle& operator=(Triangle&& other) noexcept {
        Figure<T>::operator=(std::move(other));
        return *this;
    }
    
    operator double() const override {
        if (this->vertices_.size() != 3) return 0.0;
        
        T x1 = this->vertices_[0]->getX();
        T y1 = this->vertices_[0]->getY();
        T x2 = this->vertices_[1]->getX();
        T y2 = this->vertices_[1]->getY();
        T x3 = this->vertices_[2]->getX();
        T y3 = this->vertices_[2]->getY();
        
        return 0.5 * std::abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
    }
    
    std::string getTypeName() const override {
        return "Triangle";
    }
};

#endif

