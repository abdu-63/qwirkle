#ifndef PLATEAU_H
#define PLATEAU_H

#include "structures.h"

void init_plateau(Plateau *p); // Initialise le plateau à vide
void poser_tuile(Plateau *p, int lig, int col, Forme f, Couleur c); // Place une tuile sur le plateau

#endif // PLATEAU_H
