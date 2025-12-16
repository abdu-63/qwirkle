#ifndef JOUEUR_H
#define JOUEUR_H

#include "structures.h"

void init_pioche(Pioche *p, int mode_degrade);
void completer_main(Joueur *j, Pioche *p);
void retirer_tuile_main(Joueur *j, Forme f, Couleur c);
void echanger_tuiles(Joueur *j, Pioche *p);
int possede_tuile(Joueur j, Forme f, Couleur c);

#endif // JOUEUR_H
