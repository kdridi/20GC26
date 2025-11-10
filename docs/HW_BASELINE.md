# Hardware Baseline – Référence de Performance

Ce document définit la **machine de référence minimale** utilisée pour valider
les performances des jeux du 20 Games Challenge.

Tous les jeux doivent atteindre **≥ 60 FPS** en Release sur cette configuration
ou une configuration équivalente.  
Il sert également de base pour calibrer la complexité maximale des systèmes.

---

# 1. Configuration Matérielle

## 1.1 CPU

- **Intel Core i5-8250U** (2017)
  - 4 cœurs / 8 threads
  - 1.6 GHz base, 3.4 GHz turbo
  - IPC relativement faible → bon stress-test pour les systèmes CPU-bound

> Remarque : une CPU Apple M1 ou Ryzen 5 3500U offre des performances similaires
> ou supérieures et est donc également acceptable.

---

## 1.2 GPU

- **Intel UHD 620** (iGPU)
  - OpenGL 3.3 supporté
  - Bande passante mémoire limitée
  - Faible puissance en fillrate  
    → excellent pour vérifier que le rendu est **simple, efficace et raisonnable**.

> Toute iGPU Intel 2017–2020 est validée comme baseline.
> Si un GPU plus ancien pose souci, optimiser le code plutôt que changer la baseline.

---

## 1.3 RAM

- **8 GB DDR4**, 2133 MHz
- Objectif : footprint process < **300 MB**

---

## 1.4 Stockage

- SSD SATA ou NVMe
- Temps de chargement des assets doit rester **quasi instantané**  
  (pré-allocation + assets légers)

---

# 2. Système & Logiciels

## 2.1 OS supportés

Tests obligatoires sur **l’un** des OS suivants :

- Windows 10 / 11
- Ubuntu 22.04 / 24.04
- macOS Ventura (OpenGL déprécié mais encore supporté)

## 2.2 Drivers OpenGL

- Support OpenGL 3.3 minimum
- Debug context possible mais pas nécessaire pour la baseline

---

# 3. Conditions de Test

## 3.1 Build

- **Release** (optimisations activées)
- Assertions désactivées (ou mini)
- Exceptions désactivées si spécifié dans le projet
- Rendu OpenGL actif (pas le mode ASCII)

## 3.2 Résolution

- **1280×720** (HD)  
  → Standard pour tests perf
- Optionnel : tests additionnels en 1920×1080 pour stress GPU

## 3.3 Mesures

Pour chaque jeu, collecter :

- FPS moyen (sur 30 secondes)
- FPS minimum (pire frame)
- Temps update() moyen et max
- Temps render() moyen et max
- # draw calls
- # triangles
- # allocations (doit être 0 en frame)
- Mem usage process

Stocker ces données dans `games/<id-jeu>/PERF.md`.

---

# 4. Objectifs Chiffrés (SLO)

| Domaine         | Cible Baseline    |
| --------------- | ----------------- |
| **FPS**         | ≥ 60 FPS stable   |
| **Frame-time**  | ≤ 16.6 ms         |
| **Update()**    | ≤ 5 ms            |
| **Render()**    | ≤ 8 ms            |
| **Alloc frame** | **0**             |
| **Draw calls**  | < 200 (selon jeu) |
| **Triangles**   | < 50k (selon jeu) |
| **RAM**         | < 300 MB process  |

---

# 5. Dérivations Acceptables

Une machine supérieure est valide **sans ajustement des objectifs**.

Une machine inférieure (ex : Intel HD 4000) est autorisée **uniquement en debug**,
pas pour la validation Release.

---

# 6. Automatisation Possible (optionnel)

Pour automatiser les tests :

- Script `"perf_benchmark.py"` qui :
  - lance le jeu en mode benchmark
  - récupère les FPS/min/max/tris/drawcalls via un API interne
  - écrit un JSON `benchmark.json`
  - met à jour `PERF.md`

Exemple JSON :

```json
{
	"fps_avg": 62.5,
	"fps_min": 58.9,
	"update_ms_avg": 2.7,
	"render_ms_avg": 4.9,
	"tris": 12400,
	"draw_calls": 58,
	"mem_mb": 142
}
```

---

# Conclusion

Ce document garantit que chaque jeu est :

- fluide,
- optimisé,
- raisonnable en complexité,
- et validé sur une machine modeste.

Il sert de **référence immuable** pour toutes les décisions de performance.
