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

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}