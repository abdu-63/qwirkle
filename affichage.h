#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "structures.h"

void afficher_plateau(Plateau p); // affiche le plateau
void afficher_main(Joueur j); // affiche la main
void afficher_regles_saisie(); // affiche les règles
void afficher_menu_principal(); // affiche le menu principale
void afficher_regles(); // affiche les règles
Forme char_vers_forme(char c); // convertit un caractère saisi par le joueur en type énuméré forme pour indiquer la forme de la tuile
char get_char_forme(Forme f); // convertit l'enum forme en caractère imprimable sur le plateau
const char* get_color_code(Couleur c); // fonction pour la couleur
void sauvegarder_score(char *pseudo, int score); // sauvegarde le score
void lire_scores(); // lis le score

#endif // AFFICHAGE_H
