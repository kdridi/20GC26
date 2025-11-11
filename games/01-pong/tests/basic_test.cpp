// Basic test to validate build system
#include <gtest/gtest.h>

TEST(BasicTest, CanRun) {
    EXPECT_TRUE(true);
}

auto main(int argc, char **argv) -> int {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
