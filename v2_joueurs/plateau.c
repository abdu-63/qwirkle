#include "structures.h"

void init_plateau(Plateau *p) {
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            p->grille[i][j].forme = VIDE_F;
            p->grille[i][j].couleur = VIDE_C;
        }
    }
}
