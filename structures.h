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
#define CYN "\e[0;36m"
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

// Fonctions qui modifient avec pointeur nécéssaire
void init_plateau(Plateau *p); // Initialise le plateau à vide
void init_pioche(Pioche *p, int mode_degrade); // Remplit la pioche et mélange
void completer_main(Joueur *j, Pioche *p); // Complète la main du joueur jusqu'à 6 tuiles
void retirer_tuile_main(Joueur *j, Forme f, Couleur c); // Retire une tuile spécifique de la main
void poser_tuile(Plateau *p, int lig, int col, Forme f, Couleur c); // Place une tuile sur le plateau
void echanger_tuiles(Joueur *j, Pioche *p); // Echange toute la main avec la pioche

// Fonctions en lecture seule
int possede_tuile(Joueur j, Forme f, Couleur c); // Vérifie si le joueur a la tuile
int est_coup_valide(Plateau p, int lig, int col, Forme f, Couleur c, int premier_tour); // Valide un coup selon les règles
int calculer_points(Plateau p, int lig, int col); // Calcule les points rapportés par un coup
int est_fin_partie(Pioche p, Joueur j); // Vérifie si la partie est terminée
int est_dans_plateau(int lig, int col); // Vérifie si les coordonnées sont valides

// Affichage et Utilitaires
void afficher_plateau(Plateau p); // Affiche le plateau
void afficher_main(Joueur j); // Affiche la main
void afficher_regles_saisie(); // Affiche les règles
Forme char_vers_forme(char c); // Convertit un caractère saisi en type énuméré Forme
char get_char_forme(Forme f);
const char* get_color_code(Couleur c);
void afficher_menu_principal(); // Affiche le menu principale
void afficher_regles(); // Affiche les règles

// Fonction principale du jeu qui sert a lancer la partie
void lancer_partie(int reprendre);

// Gestion des scores
void sauvegarder_score(char *pseudo, int score); // Sauvegarde le score
void lire_scores(); // Lis le score
#endif