// Basic test to validate build system
#include <gtest/gtest.h>

TEST(BasicTest, CanRun) {
    EXPECT_TRUE(true);
}

// Pong v0.1 - Ball Physics Tests
namespace pong {
    struct Ball {
        float x{400.0f};
        float y{300.0f};
    };
}

TEST(Ball, StartsAtCenterByDefault) {
    // Arrange & Act
    pong::Ball ball;

    // Assert - Ball should start at screen center (400, 300)
    EXPECT_FLOAT_EQ(ball.x, 400.0f);
    EXPECT_FLOAT_EQ(ball.y, 300.0f);
}

auto main(int argc, char **argv) -> int {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
