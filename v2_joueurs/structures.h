#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LIGNES 12
#define COLONNES 26

// couleurs ANSI
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

typedef enum { ROUGE, VERT, JAUNE, BLEU, VIOLET, ORANGE, VIDE_C } Couleur;
typedef enum { ROND, CARRE, LOSANGE, ETOILE, TREFLE, CROIX, VIDE_F } Forme;

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

// Fonctions
void init_plateau(Plateau *p);
void init_pioche(Pioche *p, int mode_degrade);
void completer_main(Joueur *j, Pioche *p);
void afficher_plateau(Plateau p);
void afficher_main(Joueur j);
char get_char_forme(Forme f);
const char* get_color_code(Couleur c);

#endif
