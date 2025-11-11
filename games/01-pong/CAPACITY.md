# Pong - Plan Mémoire et Capacités

## Philosophie

**Zéro allocation dynamique pendant la game loop.**

Toute la mémoire est préallouée au startup. Les limites sont connues,
maîtrisées et validées par tests.

## Budget Mémoire Total

```
Cible : < 10 MB pour tout le process
  - Game state  : < 1 KB
  - Rendering   : < 5 MB (buffers graphiques)
  - Overhead OS : ~4 MB
```

## Entités et Capacités

### Game Objects

```cpp
// Nombre d'entités (constants, pas de pooling nécessaire)
constexpr size_t MAX_BALLS = 1;      // Une seule balle
constexpr size_t MAX_PADDLES = 2;    // Deux raquettes
constexpr size_t MAX_ENTITIES = 3;   // Total fixe

// Calcul mémoire
sizeof(Ball)   = 16 bytes  (Vec2 pos + Vec2 vel)
sizeof(Paddle) = 20 bytes  (Vec2 pos + float speed + float height)

Total game objects = 1×16 + 2×20 = 56 bytes
```

### Game State

```cpp
struct GameState {
    Ball ball;                      // 16 bytes
    std::array<Paddle, 2> paddles;  // 40 bytes
    int scoreLeft;                  // 4 bytes
    int scoreRight;                 // 4 bytes
    enum State gameState;           // 4 bytes
    bool ballActive;                // 1 byte
    // padding                      // 7 bytes
    // Total                        // 76 bytes
};

// Arrondi à 128 bytes pour alignement cache-friendly
```

### Input Buffer

```cpp
// Pas d'historique d'inputs nécessaire pour Pong
struct InputState {
    bool p1Up, p1Down;     // 2 bytes
    bool p2Up, p2Down;     // 2 bytes
    bool quit, pause;      // 2 bytes
    // padding             // 2 bytes
    // Total               // 8 bytes
};
```

### Rendering Buffers

```cpp
// Vertex buffer (si rendu géométrique simple)
constexpr size_t MAX_VERTICES = 64;
constexpr size_t VERTEX_SIZE = 20;  // Vec2 pos + Vec2 uv + Vec4 color
Vertex buffer = 64 × 20 = 1280 bytes = ~1.3 KB

// Index buffer
constexpr size_t MAX_INDICES = 128;
Index buffer = 128 × 2 = 256 bytes

// Frame buffers (double buffering si nécessaire)
// Pour 800×600 RGBA : 800 × 600 × 4 = 1.92 MB par buffer
// → Géré par OpenGL/GPU, pas dans notre heap
```

### Audio (Optionnel v2)

```cpp
// Sons courts préchargés
constexpr size_t MAX_SOUNDS = 4;  // Paddle hit, wall hit, score, win
constexpr size_t MAX_SOUND_SIZE = 50 * 1024;  // 50 KB par son max

Total audio = 4 × 50 KB = 200 KB
```

## Allocation Strategy

### Startup (une seule fois)

```cpp
// Stack ou data segment (pas de heap)
GameState gameState;          // 128 bytes
InputState inputState;        // 8 bytes
RenderContext renderCtx;      // ~1 KB

// GPU buffers (managed par OpenGL)
glGenBuffers(VBO);            // GPU-side
glGenBuffers(IBO);            // GPU-side

Total heap allocations: 0
Total stack allocations: ~1200 bytes
```

### Per-Frame (game loop)

```
AUCUNE allocation.

Tout est mise à jour in-place :
- gameState.ball.position += velocity * dt
- gameState.scoreLeft++
- etc.
```

## Memory Layout (Cache-Friendly)

```cpp
// Hot data (accès fréquents) ensemble
struct HotData {
    alignas(64) Ball ball;          // Cache line 1
    alignas(64) Paddle paddles[2];  // Cache line 2
    alignas(64) InputState input;   // Cache line 3
};

// Cold data (accès rares) séparé
struct ColdData {
    int scoreLeft;
    int scoreRight;
    State gameState;
};
```

## Validation et Tests

### Tests Obligatoires

```cpp
TEST(Memory, NoAllocationsInGameLoop) {
    auto tracker = MemoryTracker::instance();
    tracker.reset();

    // Simulate 1000 frames
    for (int i = 0; i < 1000; ++i) {
        game.update(0.016f);
        game.render();
    }

    EXPECT_EQ(tracker.allocations(), 0);
}

TEST(Memory, TotalFootprint) {
    auto usage = getCurrentProcessMemory();
    EXPECT_LT(usage, 10 * 1024 * 1024);  // < 10 MB
}

TEST(Memory, CacheAlignment) {
    EXPECT_EQ(alignof(HotData::ball), 64);
    EXPECT_EQ(alignof(HotData::paddles), 64);
}
```

### Profiling

Vérifier avec outils :
- **Valgrind** (Linux) : Pas de leaks, pas d'allocations en loop
- **AddressSanitizer** : Détection d'erreurs mémoire
- **Custom allocator** : Logger toutes les allocations

## Limites et Contraintes

### Capacités Maximales

| Ressource       | Limite | Justification                     |
| --------------- | ------ | --------------------------------- |
| Balls           | 1      | Design du jeu                     |
| Paddles         | 2      | Design du jeu                     |
| Vertices        | 64     | 2 rectangles + 1 cercle suffisent |
| Sounds          | 4      | Événements audio simples          |
| Score max       | 11     | Règle du jeu                      |
| Frame history   | 0      | Pas de replay v1                  |

### Dépassements Impossibles

Toutes les structures sont **statiques** ou **std::array** avec tailles fixes.
Pas de `std::vector`, pas de `new`, pas de `malloc`.

Si un besoin émerge pour dépasser ces limites (ex: power-ups v2),
il faudra:
1. Mettre à jour ce document
2. Définir nouvelles capacités
3. Préallouer au startup
4. Valider par tests

## Stratégie de Dégradation

Pas applicable pour Pong v1 (capacités fixes suffisantes).

Pour versions futures avec features dynamiques :
- Utiliser `std::pmr::monotonic_buffer_resource` avec buffer préalloué
- Object pooling avec `static_vector<T, N>`
- Fallback gracieux si capacité atteinte

## Checklist de Validation

Avant de considérer Pong "terminé" :

- [ ] 0 allocations détectées en game loop (1000+ frames)
- [ ] Memory footprint < 10 MB validé
- [ ] Alignement cache vérifié (64 bytes)
- [ ] Aucun leak détecté (Valgrind clean)
- [ ] Tests automatisés en place

---

**Status** : Draft
**Date** : 2025-11-11
**Version** : 1.0
