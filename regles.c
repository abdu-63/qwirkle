#include "structures.h"

int est_dans_plateau(int lig, int col) { // paramètres lignes et colonnes
    return (lig >= 0 && lig < LIGNES && col >= 0 && col < COLONNES);
}

// PLUS DE POINTEUR (Plateau p)
int est_coup_valide(Plateau p, int lig, int col, Forme f, Couleur c, int premier_tour) {
    if (!est_dans_plateau(lig, col)) return 0;

    // Utilisation du point '.' car p n'est plus un pointeur
    if (p.grille[lig][col].forme != VIDE_F) {
        printf("Case occupee !\n");
        return 0;
    }

    int dLig[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};
    int voisins_trouves = 0;

    for (int i = 0; i < 4; i++) {
        int vL = lig + dLig[i];
        int vC = col + dCol[i];

        if (est_dans_plateau(vL, vC)) {
            Tuile voisin = p.grille[vL][vC]; // Acces direct avec .

            if (voisin.forme != VIDE_F) {
                voisins_trouves++;
                if (voisin.forme == f || voisin.couleur == c) {
                    if (voisin.forme == f && voisin.couleur == c) {
                        printf("Doublon interdit !\n");
                        return 0;
                    }
                } else {
                    printf("Ne correspond pas au voisin !\n");
                    return 0;
                }
            }
        }
    }

    if (premier_tour) return 1;
    if (voisins_trouves == 0) {
        printf("Doit toucher une autre tuile !\n");
        return 0;
    }
    return 1;
}

// PLUS DE POINTEUR (Plateau p)
int calculer_points(Plateau p, int lig, int col) {
    int points_total = 0;
    int a_forme_ligne = 0;

    // Horizontal
    int nb_h = 1;
    int c_scan = col - 1;
    while (c_scan >= 0 && p.grille[lig][c_scan].forme != VIDE_F) { nb_h++; c_scan--; }
    c_scan = col + 1;
    while (c_scan < COLONNES && p.grille[lig][c_scan].forme != VIDE_F) { nb_h++; c_scan++; }

    if (nb_h > 1) {
        points_total += nb_h;
        a_forme_ligne = 1;
        if (nb_h == 6) { points_total += 6; printf("QWIRKLE !!\n"); }
    }

    // Vertical
    int nb_v = 1;
    int l_scan = lig - 1;
    while (l_scan >= 0 && p.grille[l_scan][col].forme != VIDE_F) { nb_v++; l_scan--; }
    l_scan = lig + 1;
    while (l_scan < LIGNES && p.grille[l_scan][col].forme != VIDE_F) { nb_v++; l_scan++; }

    if (nb_v > 1) {
        points_total += nb_v;
        a_forme_ligne = 1;
        if (nb_v == 6) { points_total += 6; printf("QWIRKLE !!\n"); }
    }

    if (a_forme_ligne == 0) points_total = 1;
    return points_total;
}

// PLUS DE POINTEUR (Pioche p, Joueur j)
int est_fin_partie(Pioche p, Joueur j) {
    if (p.nb_restantes > 0) return 0;
    for (int i = 0; i < 6; i++) {
        if (j.main[i].forme != VIDE_F) return 0;
    }
    return 1;
}