# Guide de Style C++26

## Format de Base

Utiliser **clang-format moderne** avec configuration par défaut.
Les choix spécifiques ci-dessous prévalent.

## Conventions de Nommage

```cpp
// Types : PascalCase
class GameEngine {};
struct Position {};

// Functions : camelCase
auto updatePhysics() -> void;
auto calculateDistance(Point a, Point b) -> float;

// Constants : SCREAMING_SNAKE_CASE
inline constexpr auto MAX_ENTITIES = 1000;
inline constexpr float GRAVITY = 9.81f;

// Pointeurs : étoile collée à la variable
int *ptr, *other, *third;
```

## Utilisation du C++ Moderne

### Auto et Inférence

```cpp
// Utilisation MAXIMALE de auto
auto result = computeComplexType();
auto lambda = [](auto&& x) { return process(x); };

// Trailing return type TOUJOURS
auto getValue() -> int;
auto process(const Data& d) -> Result;
```

### Const-Correctness

```cpp
// Const par défaut, mutable par exception
auto calculate(const Input& in) const -> Result;
const auto value = getValue();
```

### Templates et Concepts

```cpp
// Concepts OBLIGATOIRES pour enforcement compile-time
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric T>
auto add(T a, T b) -> T {
    return a + b;
}
```

## Organisation du Code

### Structure des Fichiers

```cpp
// 1. #pragma once
// 2. Includes (ordre alphabétique)
// 3. Namespace du jeu
// 4. Concepts
// 5. Types (struct POD, puis classes)
// 6. Constantes
// 7. Fonctions
// 8. Tests (si static_assert)

#pragma once

#include <algorithm>
#include <vector>

namespace pong {

template<typename T>
concept Movable = requires(T t) { t.move(); };

struct Position { float x, y; };  // POD

class Ball {  // Non-POD
    Position pos;
public:
    auto move() -> void;
};

inline constexpr auto BALL_SPEED = 5.0f;

auto updateGame(float dt) -> void;

// Tests at the end
static_assert(sizeof(Position) == 8);

} // namespace pong
```

### Lambdas et Lisibilité

```cpp
// Nommer les lambdas complexes
auto processEntities = [](auto& entities) {
    // ...
};

// Inline pour les simples
std::ranges::sort(vec, [](auto a, auto b) { return a < b; });
```

## Règles de Sécurité

- **#pragma once** pour les guards
- **noexcept** sur toutes les fonctions qui ne throw pas
- **std::expected** pour la gestion d'erreur propre
- Maximum d'enforcement compile-time

## Code Interdit

- ❌ `using namespace std` (préparer le blobbing)
- ❌ Macros (utiliser templates/concepts)
- ❌ Variables globales mutables
- ❌ new/delete bruts
- ❌ Conversions implicites dangereuses

## Beauté du Code

Le code doit être :

- **Lisible** : Compréhensible en une lecture
- **Minimal** : Pas de code superflu
- **Expressif** : Les intentions sont claires
- **Sûr** : Les erreurs impossibles par design
