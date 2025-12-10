# Walkthrough - Versions Qwirkle

Le projet a été divisé en 4 versions progressives pour faciliter le suivi de l'avancée.

## Versions disponibles

### 1. `v1_init` - Initialisation
- **Objectif** : Mettre en place la structure de données de base et l'affichage.
- **Fonctionnalités** :
    - Affichage d'un plateau vide (12x26).
    - Structures `Plateau`, `Tuile`, `Couleur`, `Forme`.
- **Exécution** :
    ```bash
    cd v1_init
    gcc *.c -o v1 && ./v1
    ```

### 2. `v2_joueurs` - Joueurs & Pioche
- **Objectif** : Gérer les entités dynamiques (Joueurs, Pioche, Mains).
- **Fonctionnalités** :
    - Initialisation de la pioche (108 tuiles).
    - Distribution des mains (6 tuiles par joueur).
    - Affichage de l'état initial des joueurs.
- **Exécution** :
    ```bash
    cd v2_joueurs
    gcc *.c -o v2 && ./v2
    ```

### 3. `v3_gameplay` - Boucle de Jeu
- **Objectif** : Rendre le jeu interactif.
- **Fonctionnalités** :
    - Boucle principale (tour par tour).
    - Saisie des coup (ex: `ebC1`).
    - Pose de tuiles (sans validation des règles complexes).
    - Gestion de la pioche et des mains.
- **Exécution** :
    ```bash
    cd v3_gameplay
    gcc *.c -o v3 && ./v3
    ```

### 4. `v4_final` - Jeu Complet
- **Objectif** : Le jeu fini.
- **Fonctionnalités** :
    - Validation des coups (connexité, couleurs/formes uniques).
    - Calcul des points (Qwirkle !).
    - Fin de partie.
- **Exécution** :
    ```bash
    cd v4_final
    gcc *.c -o v4 && ./v4
    ```

## Structure des Fichiers
Chaque dossier contient ses propres fichiers sources `.c` et headers `.h` pour être indépendant.
