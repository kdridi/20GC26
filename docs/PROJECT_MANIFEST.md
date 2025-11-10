# 20 Games Challenge - Maîtrise C++26 avec TDD Strict

## Philosophie du Projet

Ce projet implémente le 20 Games Challenge via Claude Code en workflow multi-agents en appliquant :

- **TDD STRICT** : chaque fonction est testée AVANT d’être implémentée
- **C++26 bleeding edge** : exploration systématique des nouveautés du langage
- **Zéro allocation dynamique dans la game loop**
- **Code minimaliste** : une responsabilité par unité (fichier, classe, méthode)
- **Rendu abstrait** : backend initial OpenGL, mais architecture prête pour Vulkan/Metal/DirectX

---

# Règles Fondamentales

## 1. TDD Strict

```cpp
// Ordre OBLIGATOIRE :

1. Écrire le test
2. Vérifier que le test échoue
3. Implémenter le minimum
4. Vérifier que le test passe
5. Refactorer
```

Aucune exception à cette règle.

## 2. Gestion Mémoire

### 2.a Principes

- **Aucune allocation dynamique pendant la frame**
- Tout est préalloué au startup : pools, arenas, static buffers
- Ranges d'utilisation connus et maîtrisés
- Containers privilégiés :
  `std::array`, `static_vector<N>`, `std::pmr::*` avec `monotonic_buffer_resource`

### 2.b Documents associés

Chaque jeu doit fournir un **CAPACITY.md** :

- # maximum d’entités
- # maximum de projectiles
- buffer vidéo
- buffers audio
- plan mémoire global

## 3. Architecture

- **Fichiers minimaux** : une responsabilité par fichier
- **Classes minimales** : une responsabilité par classe
- **Méthodes courtes** : cyclomatique < 5
- **Namespaces isolés par jeu** : `namespace pong { ... }`
- **Séparation stricte** : core logique / adapter rendu
- **Game loop déterministe** : fixed timestep + accumulateur

## 4. Portabilité

- **Backend graphique initial : OpenGL 3.3 Core**
- L’abstraction `shared/graphics/` permet des backends futurs :

  - Vulkan
  - Metal (macOS recommandé)
  - DirectX

- Mode ASCII art pour les jeux 2D
- Support obligatoire : Windows / Linux / macOS

## 5. Build & Compilation

- **Modules C++26** privilégiés

- Fichiers glue pour interfaçage C tiers

- **Makefile minimal** par jeu (pas de dépendances externes)

- Profils obligatoires :

  - **Debug** : ASan/UBSan/LSan, assertions
  - **RelWithDebInfo** : optimisation + symboles
  - **Release** : opti max, assertions partielles

- Optionnel : compilation sans exceptions `-fno-exceptions`

- Flags de rigueur :

```
-Wall -Wextra -Wpedantic -Werror
```

---

# Structure Projet

```
20-games-cpp26/
├── shared/
│   ├── graphics/
│   │   ├── renderer.hpp          # Abstraction
│   │   └── opengl/               # Impl OpenGL 3.3 Core
│   └── patterns/                 # Patterns réutilisables
├── games/
│   ├── 01-pong/
│   │   ├── Makefile
│   │   ├── GAME_SPEC.md
│   │   ├── CAPACITY.md
│   │   ├── PERF.md
│   │   ├── src/
│   │   └── tests/
│   └── ...
└── docs/
    ├── PROJECT_MANIFEST.md
    ├── STYLE_GUIDE.md
    ├── CPP26_FEATURES.md
    ├── PROMPT_LIBRARY.md
    └── HW_BASELINE.md
```

---

# Protocole de Développement

Pour **CHAQUE** jeu, Claude DOIT :

1. **Relire systématiquement ce manifeste** après chaque compacting conversation
2. **Appliquer TDD strict** : test → fail → code → pass → refactor
3. Respecter **zéro allocation en frame**
4. **Commit FR** à chaque unité explicable
5. Générer les métriques obligatoires (perf, coverage, complexité)
6. Assurer un build reproductible sur Win/Linux/macOS
7. Maintenir une logique déterministe (seed RNG fixé)

---

# Gestion des Erreurs

- Utiliser `noexcept` pour éviter l'overhead des exceptions
- `std::expected<T,E>` quand approprié
- Assertions en debug

# Game Loop (Déterminisme)

- **Fixed timestep** : 16.666 ms
- **Accumulateur** pour rattraper les frames longues
- Ordre recommandé :

  1. input
  2. update logique
  3. physique
  4. rendu

- Seed RNG figé et sérialisé pour tests, replays et débugs

---

# Tests de Rendu

- Offscreen FBO → hash (xxHash/SHA1) → comparaison à golden master
- Tests ASCII fallback pour la logique 2D
- Version “headless” obligatoire pour CI

---

# Métriques Obligatoires (SLO)

Ces critères sont **bloquants**, sauf exceptions documentées.

| Catégorie   | SLO                                                    |
| ----------- | ------------------------------------------------------ |
| Coverage    | **≥ 80%** global                                       |
| Perf        | **≥ 60 FPS** sur machine `HW_BASELINE`                 |
| Complexité  | Cyclomatique < 5 par fonction                          |
| Compilation | < 2 secondes par jeu (avec cache de compilation actif) |
| Allocations | 0 allocations en frame (vérifiées via logs alloc)      |

---

# Definition of Done (par jeu)

Un jeu n’est “terminé” que lorsque :

- [ ] Tous les tests passent
- [ ] ≥ 80% coverage
- [ ] 0 alloc en frame
- [ ] 60 FPS sur machine baseline
- [ ] Replays déterministes
- [ ] Documentation complète

  - GAME_SPEC.md
  - CAPACITY.md
  - PERF.md
  - README.md

- [ ] Commits FR propres et atomiques

---

# Progression des Jeux

## Phase 1 : Fondamentaux (1–5)

- Pong, Breakout, Centipede…
- Objectif : game loop, input, collisions simples

## Phase 2 : Architecture (6–10)

- Pac-Man, Space Invaders…
- Objectif : patterns, séparation systèmes, abstraction

## Phase 3 : Performance (11–15)

- Asteroids, Missile Command…
- Objectif : zéro alloc, spatial partitioning, profiling

## Phase 4 : Maîtrise (16–20)

- Doom-like, Civilization-like…
- Objectif : architecture avancée, rendu complexe

---

# Agents de Review

- **Agent TDD** : certifie que les tests précèdent le code
- **Agent Performance** : analyse les hot paths
- **Agent Architecture** : vérifie la cohérence globale
- **Agent C++26** : propose les idiomes modernes optimaux
- **Agent Session** : rappelle ce manifeste après chaque compacting

---

# Rappel Important

⚠️ **Après CHAQUE "compacting conversation"**, rappeler à Claude :

- Documentation et commits en **FRANÇAIS**
- Code et commentaires en **ANGLAIS**
- Relire ce **PROJECT_MANIFEST.md**
- Appliquer TDD strict
