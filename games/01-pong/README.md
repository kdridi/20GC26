# Pong - Game 01

Premier jeu du 20 Games Challenge. Implémentation minimaliste de Pong en C++26 avec TDD strict.

## Prérequis

- **Compilateur** : Clang++ ou G++ avec support C++26 (`-std=c++2c`)
- **Google Test** : Framework de tests
  ```bash
  brew install googletest  # macOS
  ```

## Build & Run

```bash
# Build (debug par défaut, avec sanitizers)
make

# Lancer le jeu
make run

# Tests
make test

# Build release (optimisé)
make release

# Nettoyer
make clean
```

## Structure

```
01-pong/
├── Makefile              # Build system
├── pong/
│   └── main.cpp          # Code source
├── tests/
│   └── basic_test.cpp    # Tests GTest
└── build/                # Binaires (ignoré par git)
```

## Développement

### Approche TDD

1. Écrire un test qui échoue
2. Implémenter le code minimal pour le faire passer
3. Refactorer si nécessaire
4. Commit atomique

### Flags de Compilation

**Debug** (défaut) :
- `-std=c++2c -Wall -Wextra -Wpedantic -Werror`
- `-g -fsanitize=address,undefined`

**Release** :
- `-std=c++2c -O3 -DNDEBUG`

## Statut

- [x] Setup build system
- [x] Premier test qui passe
- [ ] Version 0.1 : Balle libre
- [ ] Version 0.2 : Une raquette
- [ ] Version 0.3 : Pong complet
- [ ] Version 0.4 : Polish

Voir [GAME_SPEC.md](GAME_SPEC.md) pour les spécifications complètes.

## Métriques Cibles

- **Performance** : 60 FPS stable
- **Mémoire** : < 10 MB, 0 allocations en frame
- **Tests** : 100% coverage des comportements
- **Code** : Complexité cyclomatique < 5

Voir [CAPACITY.md](CAPACITY.md) pour le plan mémoire.
