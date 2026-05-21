/**
 * @file test_Grid2D.cpp
 * @author Christoph Kolhoff
 */

#include<iostream>

#include<gtest/gtest.h>
#include<gmock/gmock.h>

#include "Grid2D.h"

// ----------------------------------------
// Tests without offset
struct ConstructorNoOffset : public testing::Test
{
    Grid2D<float> *grid;

    void SetUp()
    {
        size_t x = 10;
        size_t y = 5;
        float step = 2.0;

        grid = new Grid2D<float>(x, y, step);
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
    Point2D<float> pt = grid->getCoordinates(9, 4);
    float x = pt.getX();

    ASSERT_EQ(x, 18.0);
}

TEST_F(ConstructorNoOffset, CoordinateTest2Y) {
    Point2D<float> pt = grid->getCoordinates(9, 4);
    float y = pt.getY();

    ASSERT_EQ(y, 8.0);
}

TEST_F(ConstructorNoOffset, CoordinateTest2XOut1) {
    Point2D<float> pt = grid->getCoordinates(10, 4);
    float x = pt.getX();

    ASSERT_EQ(x, 18.0);
}

TEST_F(ConstructorNoOffset, CoordinateTest2YOut1) {
    Point2D<float> pt = grid->getCoordinates(2, 5);
    float y = pt.getY();

    ASSERT_EQ(y, 8.0);
}

TEST_F(ConstructorNoOffset, SetFree) {
    bool freeInit = grid->isFree(0, 0);

    grid->setObstacle(0, 0);

    bool freeInter = grid->isFree(0, 0);

    grid->setFree(0, 0);

    bool freeEnd = grid->isFree(0, 0);

    ASSERT_EQ(freeInit && !freeInter && freeEnd, true);
}

TEST_F(ConstructorNoOffset, SetObstacle) {
    bool obstInit = grid->isObstacle(2, 3);

    grid->setObstacle(2, 3);

    bool obstEnd = grid->isObstacle(2, 3);

    ASSERT_EQ(!obstInit && obstEnd, true);
}

TEST_F(ConstructorNoOffset, SetPath1) {
    bool pathInit = grid->isPath(2, 3);

    grid->setPath(2, 3);

    bool pathEnd = grid->isPath(2, 3);

    ASSERT_EQ(!pathInit && pathEnd, true);
}

TEST_F(ConstructorNoOffset, SetPath2) {
    const Point2D<float> pt(2.0, 4.0);
    bool pathInit = grid->isPath(pt);

    grid->setPath(pt);

    bool pathEnd = grid->isPath(pt);

    ASSERT_EQ(!pathInit && pathEnd, true);
}

TEST_F(ConstructorNoOffset, IsDiscovered) {
    bool ud = grid->isDiscovered(9, 3);

    ASSERT_EQ(ud, false);
}

TEST_F(ConstructorNoOffset, SetDiscovered) {
    grid->setDiscovered(10, 4);
    bool d = grid->isDiscovered(10, 4);

    ASSERT_EQ(d, true);
}

TEST_F(ConstructorNoOffset, GetIndex) {
    Point2D<float> pt(2.0, 6.0);
    
    size_t ind = grid->index(pt);

    ASSERT_EQ(ind, 31);
}

// ----------------------------------------
// Tests with offset

struct ConstructorWithOffset : public testing::Test
{
    Grid2D<float> *grid;

    void SetUp()
    {
        float x = 10.0;
        float y = 5.0;
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

TEST_F(ConstructorWithOffset, CoordinateTest1X) {
    Point2D<float> pt = grid->getCoordinates(0, 0);
    float x = pt.getX();

    ASSERT_EQ(x, -1.0);
}

TEST_F(ConstructorWithOffset, CoordinateTest1Y) {
    Point2D<float> pt = grid->getCoordinates(0, 0);
    float y = pt.getY();

    ASSERT_EQ(y, -2);
}

TEST_F(ConstructorWithOffset, CoordinateTest2X) {
    Point2D<float> pt = grid->getCoordinates(9, 4);
    float x = pt.getX();

    ASSERT_EQ(x, 17.0);
}

TEST_F(ConstructorWithOffset, CoordinateTest2Y) {
    Point2D<float> pt = grid->getCoordinates(9, 4);
    float y = pt.getY();

    ASSERT_EQ(y, 6.0);
}

TEST_F(ConstructorWithOffset, CoordinateTest2XOut1) {
    Point2D<float> pt = grid->getCoordinates(10, 4);
    float x = pt.getX();

    ASSERT_EQ(x, 17.0);
}

TEST_F(ConstructorWithOffset, CoordinateTest2YOut1) {
    Point2D<float> pt = grid->getCoordinates(2, 5);
    float y = pt.getY();

    ASSERT_EQ(y, 6.0);
}

TEST_F(ConstructorWithOffset, CoordinateTest2XOut2) {
    Point2D<float> pt = grid->getCoordinates(-1, 4);
    float y = pt.getY();

    ASSERT_EQ(y, 6.0);
}

TEST_F(ConstructorWithOffset, CoordinateTest2YOut2) {
    Point2D<float> pt = grid->getCoordinates(2, -1);
    float x = pt.getX();

    ASSERT_EQ(x, 3.0);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}