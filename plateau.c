#include "plateau.h"
#include "regles.h"

// initialise le plateau en mettant toutes les cases à vide
void init_plateau(Plateau *p) {
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            p->grille[i][j].forme = VIDE_F;
            p->grille[i][j].couleur = VIDE_C;
        }
    }
}

// place une tuile sur la grille grâce aux coordonnées
void poser_tuile(Plateau *p, int lig, int col, Forme f, Couleur c) {
    if (est_dans_plateau(lig, col)) {
        p->grille[lig][col].forme = f;
        p->grille[lig][col].couleur = c;
    }
}