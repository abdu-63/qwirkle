#ifndef REGLES_H
#define REGLES_H

#include "structures.h"

int est_dans_plateau(int lig, int col); // Vérifie si les coordonnées sont valides
int est_coup_valide(Plateau p, int lig, int col, Forme f, Couleur c, int premier_tour); // Valide un coup selon les règles
int calculer_points(Plateau p, int lig, int col); // Calcule les points rapportés par un coup
int est_fin_partie(Pioche p, Joueur j); // Vérifie si la partie est terminée

#endif // REGLES_H
