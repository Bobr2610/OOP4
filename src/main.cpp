#include <iostream>
#include <memory>
#include <iomanip>
#include "Point.h"
#include "Figure.h"
#include "Triangle.h"
#include "Square.h"
#include "Rectangle.h"
#include "Array.h"

using namespace std;

template<ScalarType T>
void printAllFigures(const Array<shared_ptr<Figure<T>>>& arr) {
    cout << "\n=== All Figures ===" << endl;
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << "\nFigure #" << (i + 1) << ":" << endl;
        arr[i]->print();
    }
}

template<ScalarType T>
double calculateTotalArea(const Array<shared_ptr<Figure<T>>>& arr) {
    double total = 0.0;
    for (size_t i = 0; i < arr.size(); ++i) {
        total += static_cast<double>(*arr[i]);
    }
    return total;
}

template<ScalarType T>
shared_ptr<Figure<T>> readFigure() {
    int type;
    cout << "Select figure type:" << endl;
    cout << "1 - Triangle" << endl;
    cout << "2 - Square" << endl;
    cout << "3 - Rectangle" << endl;
    cout << "Enter choice: ";
    cin >> type;
    
    T x, y;
    shared_ptr<Figure<T>> figure;
    
    switch (type) {
        case 1: {
            cout << "Enter center coordinates (x y): ";
            cin >> x >> y;
            Point<T> center(x, y);
            T radius;
            cout << "Enter radius of circumscribed circle: ";
            cin >> radius;
            figure = make_shared<Triangle<T>>(center, radius);
            break;
        }
        case 2: {
            cout << "Enter center coordinates (x y): ";
            cin >> x >> y;
            Point<T> center(x, y);
            T side;
            cout << "Enter side length: ";
            cin >> side;
            figure = make_shared<Square<T>>(center, side);
            break;
        }
        case 3: {
            cout << "Enter center coordinates (x y): ";
            cin >> x >> y;
            Point<T> center(x, y);
            T width, height;
            cout << "Enter width and height: ";
            cin >> width >> height;
            figure = make_shared<Rectangle<T>>(center, width, height);
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
            return nullptr;
    }
    
    return figure;
}

void demonstrateArrayWithBaseType() {
    cout << "\n=== Demonstration: Array<shared_ptr<Figure<int>>> ===" << endl;
    Array<shared_ptr<Figure<int>>> arr;
    
    // Create some figures
    auto triangle = make_shared<Triangle<int>>(Point<int>(0, 0), 5);
    auto square = make_shared<Square<int>>(Point<int>(1, 1), 4);
    auto rectangle = make_shared<Rectangle<int>>(Point<int>(2, 2), 6, 3);
    
    arr.push_back(triangle);
    arr.push_back(square);
    arr.push_back(rectangle);
    
    cout << "Array size: " << arr.size() << endl;
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << "\nElement " << i << ":" << endl;
        arr[i]->print();
    }
}

void demonstrateArrayWithDerivedType() {
    cout << "\n=== Demonstration: Array<Square<int>> ===" << endl;
    Array<Square<int>> arr;
    
    // Create some squares directly
    Square<int> sq1(Point<int>(0, 0), 5);
    Square<int> sq2(Point<int>(10, 10), 3);
    Square<int> sq3(Point<int>(20, 20), 7);
    
    arr.push_back(sq1);
    arr.push_back(sq2);
    arr.push_back(sq3);
    
    cout << "Array size: " << arr.size() << endl;
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << "\nElement " << i << ":" << endl;
        arr[i].print();
    }
}

int main() {
    cout << fixed << setprecision(2);
    
    Array<shared_ptr<Figure<double>>> figures;
    
    int choice;
    do {
        cout << "\n=== Menu ===" << endl;
        cout << "1. Add figure" << endl;
        cout << "2. Print all figures" << endl;
        cout << "3. Calculate total area" << endl;
        cout << "4. Remove figure by index" << endl;
        cout << "5. Demonstrate Array<shared_ptr<Figure<int>>>" << endl;
        cout << "6. Demonstrate Array<Square<int>>" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                auto figure = readFigure<double>();
                if (figure) {
                    figures.push_back(figure);
                    cout << "Figure added successfully!" << endl;
                }
                break;
            }
            case 2: {
                if (figures.empty()) {
                    cout << "No figures in array." << endl;
                } else {
                    printAllFigures(figures);
                }
                break;
            }
            case 3: {
                if (figures.empty()) {
                    cout << "No figures in array." << endl;
                } else {
                    double total = calculateTotalArea(figures);
                    cout << "\nTotal area of all figures: " << total << endl;
                }
                break;
            }
            case 4: {
                if (figures.empty()) {
                    cout << "No figures in array." << endl;
                } else {
                    size_t index;
                    cout << "Enter index to remove (0-" << (figures.size() - 1) << "): ";
                    cin >> index;
                    try {
                        figures.remove(index);
                        cout << "Figure at index " << index << " removed successfully!" << endl;
                    } catch (const exception& e) {
                        cout << "Error: " << e.what() << endl;
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
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);
    
    return 0;
}

