#include "structures.h"

// Convertit l'enum Forme en caractère imprimable
char get_char_forme(Forme f) {
    switch(f) {
        case ROND: return 'O';
        case CARRE: return 'C';
        case LOSANGE: return 'L';
        case ETOILE: return 'E';
        case TREFLE: return 'T';
        case CROIX: return 'X';
        default: return '.';
    }
}

// Fonction utilitaire pour la couleur
const char* get_color_code(Couleur c) {
    switch(c) {
        case ROUGE: return COLOR_RED;
        case VERT: return COLOR_GREEN;
        case JAUNE: return COLOR_YELLOW;
        case BLEU: return COLOR_BLUE;
        case VIOLET: return COLOR_MAGENTA;
        case ORANGE: return COLOR_CYAN;
        default: return COLOR_RESET;
    }
}

/*
 Affiche le plateau de jeu sur la console.
 Utilise des codes couleurs ANSI pour la lisibilité.
 Affiche les coordonnées (a-z pour colonnes, a-l pour lignes).
 */
void afficher_plateau(Plateau p) {
    printf("   ");
    // Affiche les lettres des colonnes (a-z)
    for (int j = 0; j < COLONNES; j++) {
        printf("%c ", 'a' + j);
    }
    printf("\n");

    for (int i = 0; i < LIGNES; i++) {
        // Affiche les lettres des lignes (a-l)
        printf("%c  ", 'a' + i);
        
        for (int j = 0; j < COLONNES; j++) {
            Tuile t = p.grille[i][j];
            if (t.forme == VIDE_F) {
                printf(". "); // Case vide
            } else {
                // Affiche la tuile avec sa couleur
                printf("%s%c%s ", get_color_code(t.couleur), get_char_forme(t.forme), COLOR_RESET);
            }
        }
        printf("\n");
    }
}

// Affiche la main du joueur avec les couleurs et formes.
void afficher_main(Joueur j) {
    printf("Main de %s : ", j.pseudo);
    for (int i = 0; i < 6; i++) {
        Tuile t = j.main[i];
        if (t.forme != VIDE_F) {
            // Affiche la tuile (ex: [Rouge]C )
            printf("[%s%c%d%s] ", get_color_code(t.couleur), get_char_forme(t.forme), t.couleur, COLOR_RESET);
        }
    }
    printf("\n");
}

void afficher_regles_saisie() {
    printf("Format : ligne colonne Forme Couleur (ex: 'ebC1' pour ligne e, col b, Carre, Rouge)\n");
    printf("Couleurs: 0:Rouge, 1:Vert, 2:Jaune, 3:Bleu, 4:Violet, 5:Orange\n");
    printf("Formes: O:Rond, C:Carre, L:Losange, E:Etoile, T:Trefle, X:Croix\n");
    printf("Tapez 'fin' pour arreter.\n");
}

void afficher_menu_principal() {
    printf("\nQWIRKLE\n");
    printf("1. Nouvelle Partie\n");
    printf("2. Regles du jeu\n");
    printf("3. Voir les scores\n");
    printf("4. Quitter\n");
    printf("Votre choix > ");
}

void afficher_regles() {
    printf("\nREGLES DU JEU\n");
    printf("1. Le but est d'aligner des tuiles partageant une caracteristique (Couleur ou Forme).\n");
    printf("2. Une ligne ne peut pas contenir deux tuiles identiques.\n");
    printf("3. Marquez des points egaux a la taille de la ligne creee.\n");
    printf("4. QWIRKLE : Une ligne de 6 tuiles rapporte 6 points bonus !\n");
    printf("5. Fin : Quand la pioche est vide et un joueur n'a plus de tuiles.\n");
}

// Convertit un caractère saisi en type énuméré Forme
Forme char_vers_forme(char c) {
    switch(c) {
        case 'O': return ROND;
        case 'C': return CARRE;
        case 'L': return LOSANGE;
        case 'E': return ETOILE;
        case 'T': return TREFLE;
        case 'X': return CROIX;
        default: return VIDE_F;
    }
}

// Sauvegarde le gagnant dans un fichier texte (mode "append")
void sauvegarder_score(char *pseudo, int score) {
    FILE *fichier = fopen("scores.txt", "a"); // "a" pour ajouter à la fin
    if (fichier != NULL) {
        // On écrit le nom et le score séparés par un espace
        fprintf(fichier, "%s %d\n", pseudo, score);
        fclose(fichier);
        printf("\n>>> Score sauvegarde dans l'historique ! <<<\n");
    } else {
        printf("\nErreur : Impossible de sauvegarder le score.\n");
    }
}

// Lit et affiche tout le fichier des scores
void lire_scores() {
    FILE *fichier = fopen("scores.txt", "r"); // "r" pour lire
    char nom[50];
    int score;

    printf("\nTableau des scores\n");
    if (fichier == NULL) {
        printf("Aucun score enregistre pour le moment.\n");
        return;
    }

    // On lit tant qu'il y a des lignes (format : string int)
    while (fscanf(fichier, "%s %d", nom, &score) == 2) {
        printf("%-15s : %d points\n", nom, score);
    }

    fclose(fichier);
    printf("\n");
}