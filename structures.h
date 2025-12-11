#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LIGNES 12    // Nombre de lignes du plateau de jeu
#define COLONNES 26  // Nombre de colonnes du plateau de jeu

// couleurs ANSI
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define WHT "\e[0;37m"
#define COLOR_RESET "\e[0m"

// liste de mots-clés qui correspondent à des nombres entiers
typedef enum {
    ROUGE,
    VERT,
    JAUNE,
    BLEU,
    VIOLET,
    ORANGE,
    VIDE_C
} Couleur;

typedef enum {
    ROND,
    CARRE,
    LOSANGE,
    ETOILE,
    TREFLE,
    CROIX,
    VIDE_F
} Forme;

typedef struct { // structure Tuile pour les formes et les couleurs
    Forme forme;
    Couleur couleur;
} Tuile;

typedef struct { // structure Joueur pour le nom, score, main de 6 tuiles
    char pseudo[50];
    int score;
    Tuile main[6];
} Joueur;

typedef struct { // structure Plateau qui sert pour l'affichage du plateau
    Tuile grille[LIGNES][COLONNES];
} Plateau;

typedef struct { // structure Pioche qui gère les tuiles
    Tuile tuiles[108]; // tableau des tuiles
    int nb_restantes;
    int mode; // mode de jeu (0 = normal, 1 = dégradé)
} Pioche;

// Structure de Sauvegarde
typedef struct {
    Plateau plateau;
    Pioche pioche;
    Joueur joueurs[4];
    int nb_joueurs;
    int tour;         // A qui le tour ?
    int est_premier;  // Est-ce le tout premier tour ?
} Sauvegarde;


#endif