#ifndef SQUARE_H
#define SQUARE_H

#include "Figure.h"
#include <cmath>
#include <string>

template<ScalarType T>
class Square : public Figure<T> {
public:
    // Constructor: creates a square (rotation figure)
    // center: center of the square
    // side: side length
    Square(const Point<T>& center, T side) {
        T halfSide = side / 2;
        this->vertices_.push_back(std::make_unique<Point<T>>(
            center.getX() - halfSide, center.getY() - halfSide
        ));
        this->vertices_.push_back(std::make_unique<Point<T>>(
            center.getX() + halfSide, center.getY() - halfSide
        ));
        this->vertices_.push_back(std::make_unique<Point<T>>(
            center.getX() + halfSide, center.getY() + halfSide
        ));
        this->vertices_.push_back(std::make_unique<Point<T>>(
            center.getX() - halfSide, center.getY() + halfSide
        ));
    }
    
    // Constructor from vertices
    Square(const Point<T>& v1, const Point<T>& v2, const Point<T>& v3, const Point<T>& v4) {
        this->vertices_.push_back(std::make_unique<Point<T>>(v1));
        this->vertices_.push_back(std::make_unique<Point<T>>(v2));
        this->vertices_.push_back(std::make_unique<Point<T>>(v3));
        this->vertices_.push_back(std::make_unique<Point<T>>(v4));
    }
    
    Square(const Square& other) : Figure<T>(other) {}
    Square& operator=(const Square& other) {
        Figure<T>::operator=(other);
        return *this;
    }
    Square(Square&& other) noexcept : Figure<T>(std::move(other)) {}
    Square& operator=(Square&& other) noexcept {
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
        return "Square";
    }
};

#endif // SQUARE_H

