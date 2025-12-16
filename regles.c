#include "regles.h"

int est_dans_plateau(int lig, int col) { // tuile posé est bien dans le tableau
    return (lig >= 0 && lig < LIGNES && col >= 0 && col < COLONNES);
}

int est_coup_valide(Plateau p, int lig, int col, Forme f, Couleur c, int premier_tour) {
    if (!est_dans_plateau(lig, col))
        return 0;
    if (p.grille[lig][col].forme != VIDE_F) {
        printf("Case occupée\n");
        return 0;
    }
    // regarde si tuile à côté
    int dLig[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};
    int voisins_trouves = 0;
    for (int i = 0; i < 4; i++) {
        int vL = lig + dLig[i];
        int vC = col + dCol[i];
        if (est_dans_plateau(vL, vC)) {
            Tuile voisin = p.grille[vL][vC];
            if (voisin.forme != VIDE_F) {
                voisins_trouves++;
                if (voisin.forme == f || voisin.couleur == c) {
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
    // vérifier qu'il n'y a pas de doublon de tuile dans la même ligne horizontale
    int c_scan = col - 1;
    int taille_ligne_h = 1;
    while (c_scan >= 0 && p.grille[lig][c_scan].forme != VIDE_F) {
        if (p.grille[lig][c_scan].forme == f && p.grille[lig][c_scan].couleur == c) {
            printf("Doublon dans la ligne\n");
            return 0;
        }
        taille_ligne_h++;
        c_scan--;
    }
    c_scan = col + 1;
    while (c_scan < COLONNES && p.grille[lig][c_scan].forme != VIDE_F) {
        if (p.grille[lig][c_scan].forme == f && p.grille[lig][c_scan].couleur == c) {
            printf("Doublon dans la ligne\n");
            return 0;
        }
        taille_ligne_h++;
        c_scan++;
    }
    // vérifier que la ligne ne dépasse pas 6 tuiles
    if (taille_ligne_h > 6) {
        printf("Ligne horizontale déjà complète (max 6)\n");
        return 0;
    }

    // vérifier qu'il n'y a pas de doublon de tuile dans la même colonne verticale
    int l_scan = lig - 1;
    int taille_ligne_v = 1;
    while (l_scan >= 0 && p.grille[l_scan][col].forme != VIDE_F) {
        if (p.grille[l_scan][col].forme == f && p.grille[l_scan][col].couleur == c) {
            printf("Doublon dans la colonne\n");
            return 0;
        }
        taille_ligne_v++;
        l_scan--;
    }
    l_scan = lig + 1;
    while (l_scan < LIGNES && p.grille[l_scan][col].forme != VIDE_F) {
        if (p.grille[l_scan][col].forme == f && p.grille[l_scan][col].couleur == c) {
            printf("Doublon dans la colonne\n");
            return 0;
        }
        taille_ligne_v++;
        l_scan++;
    }
    // vérifier que la colonne ne dépasse pas 6 tuiles
    if (taille_ligne_v > 6) {
        printf("Colonne verticale déjà complète (max 6)\n");
        return 0;
    }
    
    if (premier_tour)
        return 1;
    if (voisins_trouves == 0) {
        printf("Doit toucher une autre tuile\n");
        return 0;
    }
    return 1;
}

int est_fin_partie(Pioche p, Joueur j) {
    if (p.nb_restantes > 0) return 0;
    for (int i = 0; i < 6; i++) {
        if (j.main[i].forme != VIDE_F)
            return 0;
    }
    return 1;
}
int valider_serie_coups(Plateau p, Coup coups[], int n, int premier_tour) {
    if (n == 0)
        return 0;
    // vérifier l'alignement sur la même ligne ou colonne
    int meme_ligne = 1;
    int meme_colonne = 1;
    int l0 = coups[0].lig;
    int c0 = coups[0].col;
    for (int i = 1; i < n; i++) {
        if (coups[i].lig != l0)
            meme_ligne = 0;
        if (coups[i].col != c0)
            meme_colonne = 0;
    }
    if (!meme_ligne && !meme_colonne) {
        printf("Les tuiles doivent être alignées\n");
        return 0;
    }
    // simule sur un plateau temporaire pour pouvoir placer une tuile pas encore côte à côte d'une autre
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
        temp.grille[coups[i].lig][coups[i].col].forme = coups[i].forme;
        temp.grille[coups[i].lig][coups[i].col].couleur = coups[i].couleur;
    }
    return 1;
}

int calculer_score_serie_coups(Plateau p, Coup coups[], int n) {
    if (n == 0)
        return 0;
    // crée un plateau temporaire avec les mouvements appliqués
    Plateau temp = p;
    for(int i=0; i<n; i++) {
        // pose les tuiles
        temp.grille[coups[i].lig][coups[i].col].forme = coups[i].forme;
        temp.grille[coups[i].lig][coups[i].col].couleur = coups[i].couleur;
    }
    int points_total = 0;
    int main_ligne = 1;
    if (n > 1) { // test si tous sur la même ligne
        if (coups[0].lig != coups[1].lig) main_ligne = 0;
    }
    int main_axis_score = 0;
    int l_ref = coups[0].lig;
    int c_ref = coups[0].col;
    if (main_ligne) { // regarde si le joueur a joué a l'horizontale ou en vertical
        int nb_h = 1;
        int c_scan = c_ref - 1;
        // cherche jusqu'a trouver une tuile
        while (c_scan >= 0 && temp.grille[l_ref][c_scan].forme != VIDE_F) { // scan à gauche
            nb_h++;
            c_scan--;
        }
        c_scan = c_ref + 1;
        while (c_scan < COLONNES && temp.grille[l_ref][c_scan].forme != VIDE_F) { // scan à droite
            nb_h++;
            c_scan++;
        }
        if (nb_h > 1) { // test si la ligne à + d'une tuile
            main_axis_score += nb_h; // ajout de la longeur au score
            if (nb_h == 6) {
                main_axis_score += 6; printf("QWIRKLE !\n");
            }
        }
    } else {
        int nb_v = 1;
        int l_scan = l_ref - 1;
        // cherche jusqu'a trouver une tuile
        while (l_scan >= 0 && temp.grille[l_scan][c_ref].forme != VIDE_F) { // scan à gauche
            nb_v++;
            l_scan--;
        }
        l_scan = l_ref + 1;
        while (l_scan < LIGNES && temp.grille[l_scan][c_ref].forme != VIDE_F) { // scan à droite
            nb_v++;
            l_scan++;
        }
        
        if (nb_v > 1) { // test si la ligne à + d'une tuile
            main_axis_score += nb_v; // ajout de la longeur au score
            if (nb_v == 6) {
                main_axis_score += 6; printf("QWIRKLE !\n");
            }
        }
    }
    points_total += main_axis_score;
    // les axes secondaires
    for (int i = 0; i < n; i++) {
        int l = coups[i].lig;
        int c = coups[i].col;
        int cross_score = 0;
        if (main_ligne) {
            // axe vertical
            int nb_v = 1;
            int l_scan = l - 1;
            while (l_scan >= 0 && temp.grille[l_scan][c].forme != VIDE_F) { // scan en haut
                nb_v++;
                l_scan--;
            }
            l_scan = l + 1;
            while (l_scan < LIGNES && temp.grille[l_scan][c].forme != VIDE_F) { // scan en bas
                nb_v++;
                l_scan++;
            }
            
            if (nb_v > 1) { // test si la ligne à + d'une tuile
                cross_score += nb_v; // ajout de la longeur au score
                if (nb_v == 6) {
                    cross_score += 6; printf("QWIRKLE !\n");
                }
            }
        } else {
            // axe horizontal
            int nb_h = 1;
            int c_scan = c - 1;
            while (c_scan >= 0 && temp.grille[l][c_scan].forme != VIDE_F) { // scan en haut
                nb_h++;
                c_scan--;
            }
            c_scan = c + 1;
            while (c_scan < COLONNES && temp.grille[l][c_scan].forme != VIDE_F) { // scan en bas
                nb_h++;
                c_scan++;
            }
            
            if (nb_h > 1) { // test si la ligne à + d'une tuile
                cross_score += nb_h; // ajout de la longeur au score
                if (nb_h == 6) {
                    cross_score += 6; printf("QWIRKLE !\n");
                }
            }
        }
        points_total += cross_score;
    }
    // pour le début
    if (points_total == 0) points_total = 1; // test si résultat des précédant test = 0 alors veut dire que c'est le début de la partie
    return points_total;
}