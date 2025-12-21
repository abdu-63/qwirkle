<div align="center">

# 🎲 Qwirkle
<i>Jeu de stratégie de placement de tuiles en ligne de commande</i>

<p align="center">
  <a href="https://en.wikipedia.org/wiki/C_(programming_language)">
    <img alt="C" src="https://img.shields.io/badge/C-00599C?logo=c&logoColor=white">
  </a>
  <a href="https://cmake.org/">
    <img alt="CMake" src="https://img.shields.io/badge/CMake-064F8C?logo=cmake&logoColor=white">
  </a>
  <a href="https://en.wikipedia.org/wiki/Command-line_interface">
    <img alt="Terminal" src="https://img.shields.io/badge/Terminal-CLI-4EAA25?logo=gnometerminal&logoColor=white">
  </a>
  <a href="#">
    <img alt="Players" src="https://img.shields.io/badge/Joueurs-2-orange">
  </a>
</p>
</div>

## Description

Implémentation du jeu **Qwirkle** en C, jouable en mode terminal. Le jeu oppose 2 joueurs qui placent des tuiles colorées sur un plateau 12x26 en respectant les règles classiques du Qwirkle.

## Fonctionnalités

- **Plateau de jeu 12x26** : Visualisation en temps réel dans le terminal
- **2 joueurs** : Alternance automatique des tours
- **Validation des coups** : Respect des règles officielles du Qwirkle
- **Calcul des scores** : Points calculés automatiquement
- **Historique des parties** : Sauvegarde des scores

## Compilation

```bash
mkdir build && cd build
cmake ..
make
./qwirkle
```

## Structure du projet

```
qwirkle/
├── main.c           # Point d'entrée du programme
├── structures.h     # Définitions des structures de données
├── plateau.c/.h     # Gestion du plateau de jeu
├── joueur.c/.h      # Gestion des joueurs
├── jeu.c/.h         # Logique principale du jeu
├── regles.c/.h      # Validation des règles
├── affichage.c/.h   # Affichage terminal
└── CMakeLists.txt   # Configuration CMake
```
