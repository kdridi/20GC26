// Pong - Game Constants
// C++26 strict

#pragma once

namespace pong::constants {

// Screen dimensions (from GAME_SPEC.md)
inline constexpr auto SCREEN_WIDTH = 800.0F;
inline constexpr auto SCREEN_HEIGHT = 600.0F;

// Derived constants
inline constexpr auto CENTER_X = SCREEN_WIDTH / 2.0F;
inline constexpr auto CENTER_Y = SCREEN_HEIGHT / 2.0F;

} // namespace pong::constants
