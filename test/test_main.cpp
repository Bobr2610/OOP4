#include <gtest/gtest.h>
#include "Point.h"
#include "Figure.h"
#include "Triangle.h"
#include "Square.h"
#include "Rectangle.h"
#include "Array.h"
#include <memory>

TEST(PointTest, Basic) {
    Point<int> p(5, 3);
    EXPECT_EQ((p + Point<int>(2, 1)).getX(), 7);
    EXPECT_TRUE(p == Point<int>(5, 3));
}

TEST(FigureTest, Areas) {
    Triangle<double> t(Point<double>(0, 0), Point<double>(4, 0), Point<double>(0, 3));
    Square<double> s(Point<double>(0, 0), 5.0);
    Rectangle<double> r(Point<double>(0, 0), 5.0, 3.0);
    EXPECT_NEAR(static_cast<double>(t), 6.0, 0.01);
    EXPECT_NEAR(static_cast<double>(s), 25.0, 0.01);
    EXPECT_NEAR(static_cast<double>(r), 15.0, 0.01);
}

TEST(ArrayTest, Basic) {
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    arr.remove(0);
    EXPECT_EQ(arr[0], 20);
}

TEST(ArrayTest, SharedPointerFigures) {
    Array<std::shared_ptr<Figure<double>>> arr;
    arr.push_back(std::make_shared<Square<double>>(Point<double>(0, 0), 2.0));
    arr.push_back(std::make_shared<Square<double>>(Point<double>(0, 0), 3.0));
    EXPECT_EQ(arr.size(), 2);
    EXPECT_GT(static_cast<double>(*arr[0]), 0);
}

