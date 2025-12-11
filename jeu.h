#ifndef JEU_H
#define JEU_H

#include "structures.h"

void lancer_partie(int reprendre);
void effectuer_sauvegarde(Plateau p, Pioche pi, Joueur js[], int nb, int tour, int prem);
int charger_sauvegarde(Plateau *p, Pioche *pi, Joueur js[], int *nb, int *tour, int *prem);

#endif // JEU_H
