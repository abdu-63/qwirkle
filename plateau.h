#ifndef PLATEAU_H
#define PLATEAU_H

#include "structures.h"

void init_plateau(Plateau *p); // initialise le plateau en mettant toutes les cases à vide
void poser_tuile(Plateau *p, int lig, int col, Forme f, Couleur c); // place une tuile sur la grille grâce aux coordonnées

#endif // PLATEAU_H
