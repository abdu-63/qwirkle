#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LIGNES 12
#define COLONNES 26

// Couleurs ANSI
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
    Tuile tuiles[108]; // Tableau fixe
    int nb_restantes;
    int mode;
} Pioche;

// --- PROTOTYPES ---

// Fonctions qui MODIFIENT (gardent le pointeur *)
void init_plateau(Plateau *p);
void init_pioche(Pioche *p, int mode_degrade);
void completer_main(Joueur *j, Pioche *p);
void retirer_tuile_main(Joueur *j, Forme f, Couleur c);
void poser_tuile(Plateau *p, int lig, int col, Forme f, Couleur c);
void echanger_tuiles(Joueur *j, Pioche *p);

// Fonctions en LECTURE SEULE (pas de pointeur *)
int possede_tuile(Joueur j, Forme f, Couleur c);
int est_coup_valide(Plateau p, int lig, int col, Forme f, Couleur c, int premier_tour);
int calculer_points(Plateau p, int lig, int col);
int est_fin_partie(Pioche p, Joueur j);
int est_dans_plateau(int lig, int col); // <--- C'EST CETTE LIGNE QUI MANQUAIT !

// Affichage et Utilitaires
void afficher_plateau(Plateau p);
void afficher_main(Joueur j);
void afficher_regles_saisie();
Forme char_vers_forme(char c);
char get_char_forme(Forme f);
const char* get_color_code(Couleur c);
void afficher_menu_principal();
void afficher_regles();

// --- NOUVEAU : Fonction principale du jeu ---
void lancer_partie();
#endif