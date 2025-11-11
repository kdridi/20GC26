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

// Test #2: Ball moves according to velocity
TEST(Ball, MovesWithVelocity) {
    // Arrange
    pong::Ball ball;
    ball.vx = 100.0F;  // 100 pixels/sec to the right
    ball.vy = 50.0F;   // 50 pixels/sec downward
    const float dt = 0.1F;  // 100ms elapsed

    // Act
    ball.update(dt);

    // Assert - Position should be updated: pos += vel * dt
    EXPECT_FLOAT_EQ(ball.x, 410.0F);  // 400 + 100*0.1
    EXPECT_FLOAT_EQ(ball.y, 305.0F);  // 300 + 50*0.1
}
