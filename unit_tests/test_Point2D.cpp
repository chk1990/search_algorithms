#include<iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Point2D.h"

using ::testing::Exactly;

TEST(Test, Empty_ConstructorX) {
    Point2D<float> pt = Point2D<float>();

    float xDefault = pt.getX();

    EXPECT_EQ(xDefault, 0.0);
}

TEST(Test, Empty_ConstructorY) {
    Point2D<float> pt = Point2D<float>();

    float yDefault = pt.getY();

    EXPECT_EQ(yDefault, 0.0);
}

TEST(Test, Defined_ConstructorX) {
    Point2D<float> pt = Point2D<float>(1.0, 2.0);

    float xDefault = pt.getX();

    EXPECT_EQ(xDefault, 1.0);
}

TEST(Test, Defined_ConstructorY) {
    Point2D<float> pt = Point2D<float>(1.0, 2.0);

    float yDefault = pt.getY();

    EXPECT_EQ(yDefault, 2.0);
}

TEST(Test, SetX) {
    Point2D<float> pt = Point2D<float>(1.0, 2.0);

    pt.setX(5.0);

    float xDefault = pt.getX();

    EXPECT_EQ(xDefault, 5.0);
}

TEST(Test, SetY) {
    Point2D<float> pt = Point2D<float>(1.0, 2.0);

    pt.setY(5.0);

    float yDefault = pt.getY();

    EXPECT_EQ(yDefault, 5.0);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}