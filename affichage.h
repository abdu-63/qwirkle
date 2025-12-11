#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "structures.h"

void afficher_plateau(Plateau p); // Affiche le plateau
void afficher_main(Joueur j); // Affiche la main
void afficher_regles_saisie(); // Affiche les règles
void afficher_menu_principal(); // Affiche le menu principale
void afficher_regles(); // Affiche les règles
Forme char_vers_forme(char c); // Convertit un caractère saisi en type énuméré Forme
char get_char_forme(Forme f);
const char* get_color_code(Couleur c);
void sauvegarder_score(char *pseudo, int score); // Sauvegarde le score
void lire_scores(); // Lis le score

#endif // AFFICHAGE_H
