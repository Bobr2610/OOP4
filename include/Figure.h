#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"
#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include <concepts>

template<ScalarType T>
class Figure {
protected:
    std::vector<std::unique_ptr<Point<T>>> vertices_;

public:
    Figure() = default;
    virtual ~Figure() = default;
    
    // Copy constructor
    Figure(const Figure& other) {
        for (const auto& vertex : other.vertices_) {
            vertices_.push_back(std::make_unique<Point<T>>(*vertex));
        }
    }
    
    // Copy assignment
    Figure& operator=(const Figure& other) {
        if (this != &other) {
            vertices_.clear();
            for (const auto& vertex : other.vertices_) {
                vertices_.push_back(std::make_unique<Point<T>>(*vertex));
            }
        }
        return *this;
    }
    
    // Move constructor
    Figure(Figure&& other) noexcept : vertices_(std::move(other.vertices_)) {}
    
    // Move assignment
    Figure& operator=(Figure&& other) noexcept {
        if (this != &other) {
            vertices_ = std::move(other.vertices_);
        }
        return *this;
    }
    
    // Comparison operators
    bool operator==(const Figure& other) const {
        if (vertices_.size() != other.vertices_.size()) {
            return false;
        }
        for (size_t i = 0; i < vertices_.size(); ++i) {
            if (*vertices_[i] != *other.vertices_[i]) {
                return false;
            }
        }
        return true;
    }
    
    bool operator!=(const Figure& other) const {
        return !(*this == other);
    }
    
    // Conversion to double (area)
    virtual operator double() const = 0;
    
    // Get geometric center
    virtual Point<T> getCenter() const {
        if (vertices_.empty()) {
            return Point<T>(0, 0);
        }
        T sumX = 0, sumY = 0;
        for (const auto& vertex : vertices_) {
            sumX += vertex->getX();
            sumY += vertex->getY();
        }
        return Point<T>(sumX / vertices_.size(), sumY / vertices_.size());
    }
    
    // Get vertices
    const std::vector<std::unique_ptr<Point<T>>>& getVertices() const {
        return vertices_;
    }
    
    // Print figure information
    virtual void print(std::ostream& os = std::cout) const {
        os << "Figure type: " << getTypeName() << std::endl;
        os << "Geometric center: " << getCenter() << std::endl;
        os << "Vertices: ";
        for (size_t i = 0; i < vertices_.size(); ++i) {
            os << *vertices_[i];
            if (i < vertices_.size() - 1) os << ", ";
        }
        os << std::endl;
        os << "Area: " << static_cast<double>(*this) << std::endl;
    }
    
    virtual std::string getTypeName() const = 0;
};

#endif // FIGURE_H

