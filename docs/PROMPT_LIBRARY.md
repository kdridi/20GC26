# Bibliothèque de Prompts - 20 Games Challenge

## ⚠️ RÈGLE FONDAMENTALE

**TOUS les prompts en FRANÇAIS**
**Code et commentaires en ANGLAIS**

## 🔄 Prompts de Session

### Initialisation de Session

```
Nous travaillons sur le 20 Games Challenge.
Lis PROJECT_MANIFEST.md, STYLE_GUIDE.md et CPP26_FEATURES.md.
Nous sommes sur le jeu [NUMERO]-[NOM].
Rappel : TDD OBLIGATOIRE, zéro allocation dynamique dans la game loop.
```

### Après Compacting Conversation

```
Contexte : 20 Games Challenge, jeu [NUMERO].
Documentation/commits en FRANÇAIS, code/comments en ANGLAIS.
TDD strict : test AVANT implémentation.
Relis PROJECT_MANIFEST.md pour les règles.
Continue où nous nous étions arrêtés.
```

## 🧪 Prompts TDD

### Démarrage TDD

```
Pour la fonctionnalité [DESCRIPTION] :
1. Écris d'ABORD les tests (gtest/static_assert selon le cas)
2. Montre-moi les tests qui échouent
3. Implémente le MINIMUM pour passer les tests
4. Refactorise si nécessaire
Ne passe JAMAIS à l'implémentation sans tests.
```

### Tests de Propriétés

```
Génère des tests de propriétés pour [COMPOSANT] qui vérifient :
- Les invariants sont maintenus
- Pas d'allocations dynamiques
- Déterminisme avec même seed
- Performance dans les limites
Utilise static_assert quand possible.
```

## 🏗️ Prompts Architecture

### Design Initial

```
Conçois l'architecture pour [JEU] avec :
- Responsabilité unique par classe/fichier
- Zéro allocation dans la game loop
- Abstraction OpenGL permettant futur SDL2/Vulkan
- Namespace dédié au jeu
Montre d'abord les tests d'architecture.
```

### Refactoring Émergent

```
Ce pattern émerge dans plusieurs jeux.
Extrais-le dans shared/patterns/ si :
- Utilisé dans 3+ jeux
- Abstraction claire
- Testable indépendamment
Sinon, laisse dans le jeu actuel.
```

## 🎮 Prompts Spécifiques Jeux

### Physics 2D

```
Implémente la physique 2D avec :
- Collision AABB
- Pas de temps fixe avec interpolation
- Tout préalloué, aucune allocation runtime
- Version simple ET version optimisée via policy pattern
Tests d'abord !
```

### Rendering Pipeline

```
Crée le pipeline de rendu :
- Abstraction OpenGL dans shared/graphics/
- Mode ASCII art pour debug
- Batch rendering pour performance
- Zéro allocation par frame
Policy pattern pour switch simple/optimisé.
```

## 🔍 Prompts Review et Validation

### Agent Review TDD

```
Agis comme Agent TDD. Vérifie :
□ Chaque fonction a ses tests écrits AVANT
□ Tests indépendants et déterministes
□ Coverage > 80%
□ Tests de propriétés présents
Stop-moi si un critère manque.
```

### Agent Performance

```
Agis comme Agent Performance. Analyse :
□ Aucune allocation dans la game loop
□ Data layout cache-friendly
□ Opportunités SIMD identifiées
□ 60 FPS sur hardware modest
Propose optimisations via policy pattern.
```

### Agent Architecture

```
Agis comme Agent Architecture. Contrôle :
□ Une responsabilité par unité
□ Dépendances unidirectionnelles
□ Abstraction graphics correcte
□ Patterns émergents extraits si pertinent
Signale violations SOLID.
```

### Agent C++26

```
Agis comme Agent C++26. Suggère :
- Features C++26 applicables non utilisées
- Simplifications possibles avec features modernes
- Remplacements de vieux patterns
- Opportunités de métaprogrammation
Priorise sécurité > lisibilité > performance.
```

## ⚡ Prompts Optimisation

### Mesure d'Abord

```
Avant d'optimiser [COMPOSANT] :
1. Mesure performance actuelle (gbenchmark)
2. Identifie les hot paths
3. Propose optimisations
4. Implémente version optimisée À CÔTÉ de la simple
5. Compare les métriques
Utilise policy pattern pour permettre le switch.
```

### Version Lisible vs Optimisée

```
Pour [ALGORITHME], crée :
1. Version SIMPLE : claire et maintenable
2. Version OPTIMISÉE : SIMD, cache-friendly, etc.
3. Policy pattern pour choisir à la compilation
4. Benchmarks comparatifs
Les deux versions passent les mêmes tests.
```

## 🐛 Prompts Debug

### Investigation Libre

```
Bug observé : [DESCRIPTION]
Symptômes : [LISTE]
Demande-moi quelle approche préférer :
1. Analyse statique du code
2. Ajout de logs temporaires
3. Tests de régression
4. Revue architecturale
```

### Debug Systématique

```
Pour debugger [PROBLEME] :
1. Reproduis avec test minimal
2. Vérifie les invariants
3. Trace les allocations mémoire
4. Examine les race conditions possibles
5. Propose fix avec test de non-régression
```

## 📊 Prompts Métriques

### Rapport de Progression

```
Génère rapport pour jeu [NUMERO] :
- Tests écrits/passés : X/Y
- Coverage : X%
- Performance : X FPS
- Complexité cyclomatique max : X
- Features C++26 utilisées : [liste]
- Patterns émergents identifiés : [liste]
```

## 🚀 Prompts Avancés

### Preuve Formelle

```
Pour [FONCTION_CRITIQUE], établis :
- Préconditions formelles
- Postconditions formelles
- Invariants de boucle
- Preuve de terminaison
Utilise contracts C++26 si disponibles.
```

### Migration Features

```
Migre [COMPOSANT] pour utiliser [FEATURE_C++26] :
1. Montre version actuelle
2. Identifie opportunités
3. Migre progressivement
4. Compare lisibilité/performance
5. Garde les tests verts throughout
```

## 📝 Template Prompt Quotidien

```
Session jeu [NUMERO]-[NOM], jour [X].
Objectif : [FEATURE_DU_JOUR]
Contexte : [OÙ_ON_EN_EST]

1. TDD : Tests d'abord pour [FEATURE]
2. Implémentation minimale
3. Review via agents (TDD, Perf, Archi, C++26)
4. Commit atomique avec message en français
5. Mise à jour PROGRESS.md

Go !
```
