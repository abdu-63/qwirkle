#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LIGNES 12
#define COLONNES 26

// couleurs (https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a)
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define WHT "\e[0;37m"
#define COLOR_RESET "\e[0m"

// mots-clés qui correspondent à des nombres entiers (permet de mettre des mots sur les nombres)
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

typedef struct {
    Forme forme;
    Couleur couleur;
} Tuile;

typedef struct {
    char pseudo[50];
    int score;
    Tuile main[6];
} Joueur;

typedef struct {
    Tuile grille[LIGNES][COLONNES];
} Plateau;

typedef struct {
    Tuile tuiles[108];
    int nb_restantes;
    int mode;
} Pioche;

typedef struct {
    int lig;
    int col;
    Forme forme;
    Couleur couleur;
} Coup;

typedef struct {
    Plateau plateau;
    Pioche pioche;
    Joueur joueurs[4];
    int nb_joueurs;
    int tour; // A qui est le tour
    int est_premier; // si premier tour ou pas
} Sauvegarde;


#endif