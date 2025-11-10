# Features C++26 à Explorer

## Philosophie d'Utilisation

Privilégier dans l'ordre :

1. **Sécurité** : Features qui éliminent des bugs
2. **Lisibilité** : Features qui clarifient l'intention
3. **Performance** : Features qui optimisent
4. **Modernité** : Features prometteuses pour l'avenir

## Features Prioritaires (TOUS LES JEUX)

### Deducing This

```cpp
struct Entity {
    // Évite la duplication const/non-const
    auto getPosition(this auto&& self) -> decltype(auto) {
        return self.position;
    }
};
```

### Static operator()

```cpp
struct Physics {
    // Pas de this inutile
    static auto update(World& w, float dt) -> void;
    static auto operator()(World& w, float dt) -> void {
        update(w, dt);
    }
};
```

### Pattern Matching

```cpp
// Remplace les switch/if complexes
auto handleEvent(const Event& e) -> void {
    inspect(e) {
        <KeyPress> k => processKey(k.code);
        <MouseMove> m => processMouse(m.x, m.y);
        <Quit> => exitGame();
        _ => {}; // default
    }
}
```

## Features Intermédiaires (JEUX 5+)

### Reflection

```cpp
// Sérialisation automatique
template<typename T>
auto serialize(const T& obj) -> std::string {
    std::string result;
    [:expand(std::meta::members_of(^T)):] >> [&]<auto member> {
        result += serializeMember(obj.[:member:]);
    };
    return result;
}
```

### Contracts

```cpp
// Validation formelle
auto moveEntity(Entity& e, Vec2 delta)
    pre(e.isValid())
    post(e.position == old(e.position) + delta)
{
    e.position += delta;
}
```

### std::expected

```cpp
// Gestion d'erreur sans exceptions
auto loadLevel(std::string_view path)
    -> std::expected<Level, Error> {
    if (auto data = readFile(path)) {
        return parseLevel(*data);
    }
    return std::unexpected(Error::FILE_NOT_FOUND);
}
```

## Features Avancées (JEUX 10+)

### Coroutines pour Game Logic

```cpp
std::generator<GameState> gameLoop() {
    while (running) {
        co_yield processInput();
        co_yield updatePhysics();
        co_yield render();
    }
}
```

### SIMD et Parallélisme

```cpp
// Vectorisation
using vec4 = std::simd<float, 4>;

// Exécution parallèle
std::for_each(std::execution::par_unseq,
              entities.begin(), entities.end(),
              [](auto& e) { e.update(); });
```

### MDSpan pour les Grilles

```cpp
// Grilles 2D/3D efficaces
auto grid = std::mdspan<Tile,
                        std::extents<WIDTH, HEIGHT>>(data);
grid[x, y] = Tile::WALL;  // Multi-dimensional subscript
```

## Features Expérimentales

### Modules

```cpp
// game.ixx
export module game;
export auto runGame() -> void;

// main.cpp
import game;
import std;  // Standard library as module
```

### Ranges Avancés

```cpp
// Pipelines fonctionnels
auto result = entities
    | std::views::filter([](auto& e) { return e.alive; })
    | std::views::transform([](auto& e) { return e.update(); })
    | std::ranges::to<std::vector>();
```

### if consteval

```cpp
// Optimisation compile-time
auto compute(int x) -> int {
    if consteval {
        // Version compile-time
        return complexCalculation(x);
    } else {
        // Version runtime optimisée
        return cachedResult[x];
    }
}
```

## Stratégie d'Adoption

1. **Commencer simple** : Deducing this, static operator()
2. **Monter en puissance** : Pattern matching, reflection
3. **Explorer** : Coroutines, SIMD selon les besoins
4. **Innover** : Combiner les features de façon créative

## Règles d'Or

- ✅ Privilégier la **sécurité compile-time**
- ✅ Utiliser les features qui **simplifient** le code
- ✅ Adopter progressivement, pas tout d'un coup
- ❌ Éviter la complexité gratuite
- ❌ Ne pas forcer une feature si elle complique
