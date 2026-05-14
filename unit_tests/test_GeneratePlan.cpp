#include<iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "GeneratePlan.h"

using ::testing::Exactly;

struct ConstructorNoOffset : public testing::Test
{
    GeneratePlan<float> gen;

    void SetUp()
    {
        //
    }

    void TearDown()
    {
        //
    }
};

/*
TEST(T, U) {

    EXPECT_EQ(0, 0);
}
*/

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}