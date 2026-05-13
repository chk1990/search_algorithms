#include<iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Grid2D.h"

struct ConstructorNoOffset : public testing::Test
{
    Grid2D<float> *grid;

    void SetUp()
    {
        float x = 5.0;
        float y = 10.0;
        float step = 2.0;

        grid = new Grid2D<float>(x, y, step);
    }

    void TearDown()
    {
        delete grid;
    }
};

struct ConstructorWithOffset : public testing::Test
{
    Grid2D<float> *grid;

    void SetUp()
    {
        float x = 5.0;
        float y = 10.0;
        float step = 2.0;
        float xOff = -1.0;
        float yOff = -2.0;

        grid = new Grid2D<float>(x, y, step, xOff, yOff);
    }

    void TearDown()
    {
        delete grid;
    }
};

TEST_F(ConstructorNoOffset, GetWidth) {
    ASSERT_EQ(grid->getWidth(), 10.0);
}

TEST_F(ConstructorNoOffset, GetHeigth) {
    ASSERT_EQ(grid->getHeight(), 5.0);
}

TEST_F(ConstructorNoOffset, GetStep) {
    ASSERT_EQ(grid->getStep(), 2.0);
}

TEST_F(ConstructorNoOffset, CoordinateTest1X) {
    Point2D<float> pt = grid->getCoordinates(0, 0);

    float x = pt.getX();

    ASSERT_EQ(x, 0);
}

TEST_F(ConstructorNoOffset, CoordinateTest1Y) {
    Point2D<float> pt = grid->getCoordinates(0, 0);

    float y = pt.getY();

    ASSERT_EQ(y, 0);
}

TEST_F(ConstructorNoOffset, CoordinateTest2X) {
    Point2D<float> pt = grid->getCoordinates(4, 9);

    float x = pt.getX();

    ASSERT_EQ(x, 8.0);
}

TEST_F(ConstructorNoOffset, CoordinateTest2Y) {
    Point2D<float> pt = grid->getCoordinates(4, 9);

    float y = pt.getY();

    ASSERT_EQ(y, 18.0);
}

TEST_F(ConstructorWithOffset, GetWidth) {
    ASSERT_EQ(grid->getWidth(), 10.0);
}

TEST_F(ConstructorWithOffset, GetHeigth) {
    ASSERT_EQ(grid->getHeight(), 5.0);
}

TEST_F(ConstructorWithOffset, GetStep) {
    ASSERT_EQ(grid->getStep(), 2.0);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}