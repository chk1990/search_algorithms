#include<iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "GeneratePlan.h"

using ::testing::Exactly;

/*
TEST(T, U) {

    EXPECT_EQ(0, 0);
}
*/

int main(int argc, char* argv[]) {
    //testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();

    GeneratePlan<float> generator();

    generator.printPlan2D(1, "plan.dat");

    return 0;
}