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

// Test #3a: Ball bounces on top wall (y=0)
TEST(Ball, BouncesOnTopWall) {
    // Arrange - Ball moving upward, about to hit top
    pong::Ball ball;
    ball.y = 5.0F;
    ball.vy = -100.0F;  // Moving up

    // Act
    ball.update(0.1F);  // y would become -5 without bounce
    ball.bounceOnWalls();

    // Assert
    EXPECT_FLOAT_EQ(ball.y, 0.0F);      // Clamped to wall
    EXPECT_FLOAT_EQ(ball.vy, 100.0F);   // Velocity inverted
}

// Test #3b: Ball bounces on bottom wall (y=600)
TEST(Ball, BouncesOnBottomWall) {
    // Arrange - Ball moving downward, about to hit bottom
    pong::Ball ball;
    ball.y = 595.0F;
    ball.vy = 100.0F;  // Moving down

    // Act
    ball.update(0.1F);  // y would become 605 without bounce
    ball.bounceOnWalls();

    // Assert
    EXPECT_FLOAT_EQ(ball.y, 600.0F);    // Clamped to wall
    EXPECT_FLOAT_EQ(ball.vy, -100.0F);  // Velocity inverted
}

// Test #3c: Ball does not bounce when not hitting walls
TEST(Ball, DoesNotBounceWhenNotHittingWalls) {
    // Arrange - Ball in middle of screen
    pong::Ball ball;
    ball.y = 300.0F;
    ball.vy = 50.0F;

    // Act
    ball.bounceOnWalls();

    // Assert - Velocity unchanged
    EXPECT_FLOAT_EQ(ball.y, 300.0F);
    EXPECT_FLOAT_EQ(ball.vy, 50.0F);
}
