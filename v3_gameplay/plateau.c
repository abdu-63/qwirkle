#include "structures.h"

void init_plateau(Plateau *p) {
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            p->grille[i][j].forme = VIDE_F;
            p->grille[i][j].couleur = VIDE_C;
        }
    }
}

int est_dans_plateau(int lig, int col) {
    return (lig >= 0 && lig < LIGNES && col >= 0 && col < COLONNES);
}

void poser_tuile(Plateau *p, int lig, int col, Forme f, Couleur c) {
    if (est_dans_plateau(lig, col)) {
        p->grille[lig][col].forme = f;
        p->grille[lig][col].couleur = c;
    }
}
