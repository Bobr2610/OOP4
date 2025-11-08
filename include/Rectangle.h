#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"
#include <cmath>
#include <string>

template<ScalarType T>
class Rectangle : public Figure<T> {
public:
    // Constructor: creates a rectangle inscribed in a circle
    // center: center of the circumscribed circle
    // width: width of the rectangle
    // height: height of the rectangle
    Rectangle(const Point<T>& center, T width, T height) {
        T halfWidth = width / 2;
        T halfHeight = height / 2;
        
        this->vertices_.push_back(std::make_unique<Point<T>>(
            center.getX() - halfWidth, center.getY() - halfHeight
        ));
        this->vertices_.push_back(std::make_unique<Point<T>>(
            center.getX() + halfWidth, center.getY() - halfHeight
        ));
        this->vertices_.push_back(std::make_unique<Point<T>>(
            center.getX() + halfWidth, center.getY() + halfHeight
        ));
        this->vertices_.push_back(std::make_unique<Point<T>>(
            center.getX() - halfWidth, center.getY() + halfHeight
        ));
    }
    
    // Constructor from vertices
    Rectangle(const Point<T>& v1, const Point<T>& v2, const Point<T>& v3, const Point<T>& v4) {
        this->vertices_.push_back(std::make_unique<Point<T>>(v1));
        this->vertices_.push_back(std::make_unique<Point<T>>(v2));
        this->vertices_.push_back(std::make_unique<Point<T>>(v3));
        this->vertices_.push_back(std::make_unique<Point<T>>(v4));
    }
    
    Rectangle(const Rectangle& other) : Figure<T>(other) {}
    Rectangle& operator=(const Rectangle& other) {
        Figure<T>::operator=(other);
        return *this;
    }
    Rectangle(Rectangle&& other) noexcept : Figure<T>(std::move(other)) {}
    Rectangle& operator=(Rectangle&& other) noexcept {
        Figure<T>::operator=(std::move(other));
        return *this;
    }
    
    operator double() const override {
        if (this->vertices_.size() != 4) return 0.0;
        
        // Calculate area using cross product (shoelace formula)
        T sum = 0;
        for (size_t i = 0; i < 4; ++i) {
            size_t j = (i + 1) % 4;
            sum += this->vertices_[i]->getX() * this->vertices_[j]->getY();
            sum -= this->vertices_[j]->getX() * this->vertices_[i]->getY();
        }
        return 0.5 * std::abs(sum);
    }
    
    std::string getTypeName() const override {
        return "Rectangle";
    }
};

#endif // RECTANGLE_H

