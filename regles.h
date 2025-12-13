#ifndef REGLES_H
#define REGLES_H

#include "structures.h"

int est_dans_plateau(int lig, int col); // test si les coordonnées sont valides
int est_coup_valide(Plateau p, int lig, int col, Forme f, Couleur c, int premier_tour); // valide un coup selon les règles
int calculer_points(Plateau p, int lig, int col); // calcule les points rapportés par un coup
int est_fin_partie(Pioche p, Joueur j); // test si la partie est terminée

#endif // REGLES_H
