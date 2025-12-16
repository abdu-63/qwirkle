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
    while (c_scan >= 0 && p.grille[lig][c_scan].forme != VIDE_F) {
        nb_h++;
        c_scan--;
    }
    c_scan = col + 1;
    while (c_scan < COLONNES && p.grille[lig][c_scan].forme != VIDE_F) {
        nb_h++;
        c_scan++;
    }

    if (nb_h > 1) {
        points_total += nb_h;
        a_forme_ligne = 1;
        if (nb_h == 6) { points_total += 6; printf("QWIRKLE !\n"); } // bonus de 6 points
    }

    // comptage vertical (Haut + Bas)
    int nb_v = 1;
    int l_scan = lig - 1;
    while (l_scan >= 0 && p.grille[l_scan][col].forme != VIDE_F) {
        nb_v++;
        l_scan--;
    }
    l_scan = lig + 1;
    while (l_scan < LIGNES && p.grille[l_scan][col].forme != VIDE_F) {
        nb_v++;
        l_scan++;
    }

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
// Vérifie si une série de coups est valide
int valider_serie_coups(Plateau p, Coup coups[], int n, int premier_tour) {
    if (n == 0) return 0;
    
    // Vérifier l'alignement (tous sur la même ligne ou même colonne)
    int meme_ligne = 1;
    int meme_colonne = 1;
    
    int l0 = coups[0].lig;
    int c0 = coups[0].col;
    
    for (int i = 1; i < n; i++) {
        if (coups[i].lig != l0) meme_ligne = 0;
        if (coups[i].col != c0) meme_colonne = 0;
    }
    
    if (!meme_ligne && !meme_colonne) {
        printf("Les tuiles doivent etre alignees\n");
        return 0;
    }

    // Simulation sur un plateau temporaire
    Plateau temp = p;
    for (int i = 0; i < n; i++) {
        int est_premier_eff;
        if (i == 0) {
            est_premier_eff = premier_tour;
        } else {
            est_premier_eff = 0;
        }
        
        if (!est_coup_valide(temp, coups[i].lig, coups[i].col, coups[i].forme, coups[i].couleur, est_premier_eff)) {
            return 0;
        }
        // On pose la tuile sur le temp pour le coup suivant
        temp.grille[coups[i].lig][coups[i].col].forme = coups[i].forme;
        temp.grille[coups[i].lig][coups[i].col].couleur = coups[i].couleur;
    }
    
    return 1;
}

int calculer_score_serie_coups(Plateau p, Coup coups[], int n) {
    if (n == 0) return 0;
    
    // Créer un plateau temporaire avec des mouvements appliqués
    Plateau temp = p;
    for(int i=0; i<n; i++) {
        temp.grille[coups[i].lig][coups[i].col].forme = coups[i].forme;
        temp.grille[coups[i].lig][coups[i].col].couleur = coups[i].couleur;
    }

    int points_total = 0;
    
    // Détermination de l'axe principal
    int main_ligne = 1; // tous sur la même ligne?
    if (n > 1) {
        if (coups[0].lig != coups[1].lig) main_ligne = 0;
    }
    
    // Calculer l'axe principal
    int main_axis_score = 0;
    int l_ref = coups[0].lig;
    int c_ref = coups[0].col;
    
    if (main_ligne) {
        int nb_h = 1;
        int c_scan = c_ref - 1;
        while (c_scan >= 0 && temp.grille[l_ref][c_scan].forme != VIDE_F) {
            nb_h++;
            c_scan--;
        }
        c_scan = c_ref + 1;
        while (c_scan < COLONNES && temp.grille[l_ref][c_scan].forme != VIDE_F) {
            nb_h++;
            c_scan++;
        }
        
        if (nb_h > 1) {
            main_axis_score += nb_h;
            if (nb_h == 6) { main_axis_score += 6; printf("QWIRKLE (Ligne)\n"); }
        }
    } else {
        int nb_v = 1;
        int l_scan = l_ref - 1;
        while (l_scan >= 0 && temp.grille[l_scan][c_ref].forme != VIDE_F) {
            nb_v++;
            l_scan--;
        }
        l_scan = l_ref + 1;
        while (l_scan < LIGNES && temp.grille[l_scan][c_ref].forme != VIDE_F) {
            nb_v++;
            l_scan++;
        }
        
        if (nb_v > 1) {
            main_axis_score += nb_v;
            if (nb_v == 6) { main_axis_score += 6; printf("QWIRKLE (Colonne)\n"); }
        }
    }
    points_total += main_axis_score;

    // Calculer les axes secondaires pour CHAQUE tuile
    for (int i = 0; i < n; i++) {
        int l = coups[i].lig;
        int c = coups[i].col;
        int cross_score = 0;
        
        if (main_ligne) {
            // Axe secondaire = Vertical
            int nb_v = 1;
            int l_scan = l - 1;
            while (l_scan >= 0 && temp.grille[l_scan][c].forme != VIDE_F) {
                nb_v++;
                l_scan--;
            }
            l_scan = l + 1;
            while (l_scan < LIGNES && temp.grille[l_scan][c].forme != VIDE_F) {
                nb_v++;
                l_scan++;
            }
            
            if (nb_v > 1) {
                cross_score += nb_v;
                if (nb_v == 6) { cross_score += 6; printf("QWIRKLE (Croix)\n"); }
            }
        } else {
            // Axe secondaire = Horizontal
            int nb_h = 1;
            int c_scan = c - 1;
            while (c_scan >= 0 && temp.grille[l][c_scan].forme != VIDE_F) {
                nb_h++;
                c_scan--;
            }
            c_scan = c + 1;
            while (c_scan < COLONNES && temp.grille[l][c_scan].forme != VIDE_F) {
                nb_h++;
                c_scan++;
            }
            
            if (nb_h > 1) {
                cross_score += nb_h;
                if (nb_h == 6) { cross_score += 6; printf("QWIRKLE (Croix) !\n"); }
            }
        }
        points_total += cross_score;
    }

    // Cas particulier: 1 seule tuile isolée
    if (points_total == 0) points_total = 1;
    return points_total;
}