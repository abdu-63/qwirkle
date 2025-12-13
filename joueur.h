#ifndef JOUEUR_H
#define JOUEUR_H

#include "structures.h"

void init_pioche(Pioche *p, int mode_degrade); // initialise la picohe
void completer_main(Joueur *j, Pioche *p); // ajoute une tuile dans la main après la pose de tuile
void retirer_tuile_main(Joueur *j, Forme f, Couleur c); // retire une tuile spécifique de la main du joueur
void echanger_tuiles(Joueur *j, Pioche *p); // échange les tuiles de la main du joueur avec la pioche
int possede_tuile(Joueur j, Forme f, Couleur c); // vérifie que le joueur peut changer de tuile si il n'en a pas besoin

#endif // JOUEUR_H
