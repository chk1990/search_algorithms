/**
 * @file test_AStar2D.cpp
 * @author Christoph Kolhoff
 */

#include<cmath>
#include<iostream>

#include<gtest/gtest.h>
#include<gmock/gmock.h>

#include "AStar2D.h"

struct AStar2DTest : public testing::Test
{
    AStar2D<float> *astar;

    void SetUp()
    {
        astar = new AStar2D<float>("../data_environment/plan1.dat");
    }

    void TearDown()
    {
        delete astar;
    }
};

TEST_F(AStar2DTest, SetGetGoal) {
    astar->setGoal(Point2D<float>(10.0, 8.0));

    Point2D<float> pt = astar->getGoal();
    EXPECT_EQ(10.0 == pt.getX() && 8.0 == pt.getY(), true);
}

TEST_F(AStar2DTest, SetGetBegin) {
    astar->setBegin(Point2D<float>(2.0, 4.0));

    Point2D<float> pt = astar->getPath(0);

    EXPECT_EQ(2.0 == pt.getX() && 4.0 == pt.getY(), true);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}