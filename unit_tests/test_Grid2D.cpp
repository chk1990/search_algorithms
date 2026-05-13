#include<iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Grid2D.h"

//using ::testing::Exactly;

struct ConstructorNoOffset : public testing::Test
{
    Grid2D<float> *grid;

    void SetUp()
    {
        grid = new Grid2D<float>(5.0, 10.0, 2.0);
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
    ASSERT_EQ(grid->getHeigt(), 5.0);
}

TEST_F(ConstructorNoOffset, GetStep) {
    ASSERT_EQ(grid->getStep(), 2.0);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}