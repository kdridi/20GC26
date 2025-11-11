// Ball Tests - TDD for Pong Ball entity
#include "../pong/ball.hpp"

#include <gtest/gtest.h>

// Test #1: Ball starts at center by default
TEST(Ball, StartsAtCenterByDefault) {
    // Arrange & Act
    pong::Ball ball;

    // Assert - Ball should start at screen center (400, 300)
    EXPECT_FLOAT_EQ(ball.x, 400.0F);
    EXPECT_FLOAT_EQ(ball.y, 300.0F);
}
