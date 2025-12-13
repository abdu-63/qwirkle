#ifndef JEU_H
#define JEU_H

#include "structures.h"

void lancer_partie(int reprendre); // fonction principale pour les parties
void effectuer_sauvegarde(Plateau p, Pioche pi, Joueur js[], int nb, int tour, int prem); // sauvegarde la partie
int charger_sauvegarde(Plateau *p, Pioche *pi, Joueur js[], int *nb, int *tour, int *prem); // reprend la partie sauvgardé

#endif // JEU_H
