// Pong - Ball Entity
// C++26 strict

#pragma once

#include <compare>

#include "constants.hpp"

namespace pong {

// Ball entity - Simple POD structure
// Starts at screen center by default with zero velocity
struct Ball {
    float x{constants::CENTER_X};
    float y{constants::CENTER_Y};
    float vx{0.0F};  // Velocity in pixels/second
    float vy{0.0F};

    // Update position based on velocity and delta time
    // Physics: position(t+dt) = position(t) + velocity * dt
    constexpr auto update(float dt) noexcept -> void {
        x += vx * dt;
        y += vy * dt;
    }

    // Bounce on walls - Handles collision with top and bottom walls
    // Reflects vertical velocity and clamps position to boundaries
    constexpr auto bounceOnWalls() noexcept -> void {
        // Top wall (y=0)
        if (y <= 0.0F) {
            y = 0.0F;
            vy = -vy;
        }
        // Bottom wall (y=SCREEN_HEIGHT)
        if (y >= constants::SCREEN_HEIGHT) {
            y = constants::SCREEN_HEIGHT;
            vy = -vy;
        }
    }

    // Spaceship operator for comparisons (useful for tests)
    auto operator<=>(const Ball &) const = default;
};

} // namespace pong
