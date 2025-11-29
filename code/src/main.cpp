#include <iostream>
#include <memory>
#include <iomanip>
#include "Point.h"
#include "Figure.h"
#include "Triangle.h"
#include "Square.h"
#include "Rectangle.h"
#include "Array.h"

template<ScalarType T>
void printAllFigures(const Array<std::shared_ptr<Figure<T>>>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << "\nFigure " << i << ":" << std::endl;
        arr[i]->print();
    }
}

template<ScalarType T>
double calculateTotalArea(const Array<std::shared_ptr<Figure<T>>>& arr) {
    double total = 0.0;
    for (size_t i = 0; i < arr.size(); ++i) {
        total += static_cast<double>(*arr[i]);
    }
    return total;
}

template<ScalarType T>
std::shared_ptr<Figure<T>> readFigure() {
    int type;
    std::cout << "Figure type (1-Triangle, 2-Square, 3-Rectangle): ";
    std::cin >> type;
    
    T x, y;
    std::shared_ptr<Figure<T>> figure;
    
    switch (type) {
        case 1: {
            std::cout << "Center (x y) and radius: ";
            std::cin >> x >> y;
            Point<T> center(x, y);
            T radius;
            std::cin >> radius;
            figure = std::make_shared<Triangle<T>>(center, radius);
            break;
        }
        case 2: {
            std::cout << "Center (x y) and side: ";
            std::cin >> x >> y;
            Point<T> center(x, y);
            T side;
            std::cin >> side;
            figure = std::make_shared<Square<T>>(center, side);
            break;
        }
        case 3: {
            std::cout << "Center (x y), width and height: ";
            std::cin >> x >> y;
            Point<T> center(x, y);
            T width, height;
            std::cin >> width >> height;
            figure = std::make_shared<Rectangle<T>>(center, width, height);
            break;
        }
        default:
            std::cout << "Invalid type" << std::endl;
            return nullptr;
    }
    
    return figure;
}

void demonstrateArrayWithBaseType() {
    std::cout << "\nArray<shared_ptr<Figure<int>>>:" << std::endl;
    Array<std::shared_ptr<Figure<int>>> arr;
    
    auto triangle = std::make_shared<Triangle<int>>(Point<int>(0, 0), 5);
    auto square = std::make_shared<Square<int>>(Point<int>(1, 1), 4);
    auto rectangle = std::make_shared<Rectangle<int>>(Point<int>(2, 2), 6, 3);
    
    arr.push_back(triangle);
    arr.push_back(square);
    arr.push_back(rectangle);
    
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i]->print();
    }
}

void demonstrateArrayWithDerivedType() {
    std::cout << "\nArray<Square<int>>:" << std::endl;
    Array<Square<int>> arr;
    
    Square<int> sq1(Point<int>(0, 0), 5);
    Square<int> sq2(Point<int>(10, 10), 3);
    Square<int> sq3(Point<int>(20, 20), 7);
    
    arr.push_back(sq1);
    arr.push_back(sq2);
    arr.push_back(sq3);
    
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i].print();
    }
}

int main() {
    std::cout << std::fixed << std::setprecision(2);
    
    Array<std::shared_ptr<Figure<double>>> figures;
    
    int choice;
    do {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Add figure" << std::endl;
        std::cout << "2. Print all" << std::endl;
        std::cout << "3. Total area" << std::endl;
        std::cout << "4. Remove by index" << std::endl;
        std::cout << "5. Demo Array<shared_ptr<Figure<int>>>" << std::endl;
        std::cout << "6. Demo Array<Square<int>>" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                auto figure = readFigure<double>();
                if (figure) {
                    figures.push_back(figure);
                }
                break;
            }
            case 2: {
                if (figures.empty()) {
                    std::cout << "Empty" << std::endl;
                } else {
                    printAllFigures(figures);
                }
                break;
            }
            case 3: {
                if (figures.empty()) {
                    std::cout << "Empty" << std::endl;
                } else {
                    double total = calculateTotalArea(figures);
                    std::cout << "Total area: " << total << std::endl;
                }
                break;
            }
            case 4: {
                if (figures.empty()) {
                    std::cout << "Empty" << std::endl;
                } else {
                    size_t index;
                    std::cout << "Index (0-" << (figures.size() - 1) << "): ";
                    std::cin >> index;
                    try {
                        figures.remove(index);
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                }
                break;
            }
            case 5: {
                demonstrateArrayWithBaseType();
                break;
            }
            case 6: {
                demonstrateArrayWithDerivedType();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Invalid" << std::endl;
        }
    } while (choice != 0);
    
    return 0;
}

