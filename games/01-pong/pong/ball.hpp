// Pong - Ball Entity
// C++26 strict

#pragma once

#include <compare>

#include "constants.hpp"

namespace pong {

// Ball entity - Simple POD structure
// Starts at screen center by default
struct Ball {
    float x{constants::CENTER_X};
    float y{constants::CENTER_Y};

    // Spaceship operator for comparisons (useful for tests)
    auto operator<=>(const Ball &) const = default;
};

} // namespace pong
