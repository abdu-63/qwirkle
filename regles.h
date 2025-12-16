#ifndef REGLES_H
#define REGLES_H

#include "structures.h"

int est_dans_plateau(int lig, int col);
int est_coup_valide(Plateau p, int lig, int col, Forme f, Couleur c, int premier_tour);
int calculer_points(Plateau p, int lig, int col);
int est_fin_partie(Pioche p, Joueur j);
int valider_serie_coups(Plateau p, Coup coups[], int n, int premier_tour);
int calculer_score_serie_coups(Plateau p, Coup coups[], int n);

#endif // REGLES_H
