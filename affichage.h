#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "structures.h"

void afficher_plateau(Plateau p);
void afficher_main(Joueur j);
void afficher_regles_saisie();
void afficher_menu_principal();
void afficher_regles();
Forme char_vers_forme(char c); // convertit un caractère saisi par le joueur en type énuméré forme pour indiquer la forme de la tuile
char get_char_forme(Forme f);
const char* get_color_code(Couleur c);
void sauvegarder_score(char *pseudo, int score);
void lire_scores();
void sauvegarder_derniere_partie(Joueur joueurs[], int nb_joueurs);
void lire_derniere_partie();

#endif // AFFICHAGE_H
