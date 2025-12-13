#include "regles.h"

int est_dans_plateau(int lig, int col) { // paramètres lignes et colonnes
    // vérifie que les coordonnées sont bien dans les limites du tableau (0-11 et 0-25)
    return (lig >= 0 && lig < LIGNES && col >= 0 && col < COLONNES);
}

int est_coup_valide(Plateau p, int lig, int col, Forme f, Couleur c, int premier_tour) {
    // test les limites du plateau
    if (!est_dans_plateau(lig, col)) return 0;

    // test que la case n'est pas déjà prise
    if (p.grille[lig][col].forme != VIDE_F) {
        printf("Case occupée\n");
        return 0;
    }

    // vecteurs de direction pour vérifier les 4 voisins (Haut, Bas, Gauche, Droite)
    int dLig[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};
    int voisins_trouves = 0;

    for (int i = 0; i < 4; i++) {
        int vL = lig + dLig[i];
        int vC = col + dCol[i];

        if (est_dans_plateau(vL, vC)) {
            Tuile voisin = p.grille[vL][vC]; // acces direct avec .

            if (voisin.forme != VIDE_F) {
                voisins_trouves++;
                // la tuile doit partager soit la forme soit la couleur avec son voisin
                if (voisin.forme == f || voisin.couleur == c) {
                    // interdit de poser une tuile identique juste à côté
                    if (voisin.forme == f && voisin.couleur == c) {
                        printf("Doublon interdit\n");
                        return 0;
                    }
                } else {
                    printf("Ne correspond pas au voisin\n");
                    return 0;
                }
            }
        }
    }

    // test si c'est le tout premier tour car pas besoin de voisins
    if (premier_tour) return 1;
    // sinon la tuile doit obligatoirement toucher une tuile existante
    if (voisins_trouves == 0) {
        printf("Doit toucher une autre tuile\n");
        return 0;
    }
    return 1;
}

int calculer_points(Plateau p, int lig, int col) {
    int points_total = 0;
    int a_forme_ligne = 0; // indicateur pour savoir si la tuile a étendu une ligne

    // comptage horizontal (Gauche + Droite)
    int nb_h = 1;
    int c_scan = col - 1;
    while (c_scan >= 0 && p.grille[lig][c_scan].forme != VIDE_F) { nb_h++; c_scan--; }
    c_scan = col + 1;
    while (c_scan < COLONNES && p.grille[lig][c_scan].forme != VIDE_F) { nb_h++; c_scan++; }

    if (nb_h > 1) {
        points_total += nb_h;
        a_forme_ligne = 1;
        if (nb_h == 6) { points_total += 6; printf("QWIRKLE !\n"); } // bonus de 6 points
    }

    // comptage vertical (Haut + Bas)
    int nb_v = 1;
    int l_scan = lig - 1;
    while (l_scan >= 0 && p.grille[l_scan][col].forme != VIDE_F) { nb_v++; l_scan--; }
    l_scan = lig + 1;
    while (l_scan < LIGNES && p.grille[l_scan][col].forme != VIDE_F) { nb_v++; l_scan++; }

    if (nb_v > 1) {
        points_total += nb_v;
        a_forme_ligne = 1;
        if (nb_v == 6) { points_total += 6; printf("QWIRKLE !\n"); } // bonus de 6 points
    }

    // test si la tuile est isolée elle vaut 1 point
    if (a_forme_ligne == 0) points_total = 1;
    return points_total;
}

int est_fin_partie(Pioche p, Joueur j) {
    // la partie s'arrête quand la pioche est vide et qu'un joueur a vidé sa main
    if (p.nb_restantes > 0) return 0;
    for (int i = 0; i < 6; i++) {
        if (j.main[i].forme != VIDE_F) return 0;
    }
    return 1;
}