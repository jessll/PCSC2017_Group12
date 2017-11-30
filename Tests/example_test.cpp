//
// Created by mariella on 30.11.17.
//
#include "gtest/gtest.h"

TEST(ExampleTest, HandlesInput) {
EXPECT_EQ(1, 1.0);
}


int func(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}