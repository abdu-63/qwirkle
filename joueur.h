#ifndef JOUEUR_H
#define JOUEUR_H

#include "structures.h"

void init_pioche(Pioche *p, int mode_degrade); // Remplit la pioche et mélange
void completer_main(Joueur *j, Pioche *p); // Complète la main du joueur jusqu'à 6 tuiles
void retirer_tuile_main(Joueur *j, Forme f, Couleur c); // Retire une tuile spécifique de la main
void echanger_tuiles(Joueur *j, Pioche *p); // Echange toute la main avec la pioche
int possede_tuile(Joueur j, Forme f, Couleur c); // Vérifie si le joueur a la tuile

#endif // JOUEUR_H
