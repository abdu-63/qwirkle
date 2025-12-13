#include "affichage.h"

// convertit l'enum forme en caractère imprimable sur le plateau
char get_char_forme(Forme f) {
    switch(f) {
        case ROND:
            return 'O';
        case CARRE:
            return 'C';
        case LOSANGE:
            return 'L';
        case ETOILE:
            return 'E';
        case TREFLE:
            return 'T';
        case CROIX:
            return 'X';
        default:
            return '.'; // case vide
    }
}

// fonction pour la couleur
const char* get_color_code(Couleur c) {
    switch(c) {
        case ROUGE:
            return RED;
        case VERT:
            return GRN;
        case JAUNE:
            return YEL;
        case BLEU:
            return BLU;
        case VIOLET:
            return MAG;
        case ORANGE:
            return WHT;
        default:
            return COLOR_RESET;
    }
}

// Affiche le plateau de jeu sur la console avec boucle for
void afficher_plateau(Plateau p) {
    printf("   ");
    // boucle pour afficher les lettres des colonnes (a-z car 26)
    for (int j = 0; j < COLONNES; j++) {
        printf("%c ", 'a' + j);
    }
    printf("\n");

    for (int i = 0; i < LIGNES; i++) {
        // boucle pour afficher les lettres des lignes (a-l car 12)
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

// affiche la main de 6 du joueur avec les couleurs et formes.
void afficher_main(Joueur j) {
    printf("Main de %s : ", j.pseudo);
    for (int i = 0; i < 6; i++) {
        Tuile t = j.main[i];
        if (t.forme != VIDE_F) {
            // Affiche la tuile
            printf("[%s%c%d%s] ", get_color_code(t.couleur), get_char_forme(t.forme), t.couleur, COLOR_RESET);
        }
    }
    printf("\n");
}

// procedure pour affichier les règles de saisie
void afficher_regles_saisie() {
    printf("Format : ligne colonne Forme Couleur (ex: ebC1)\n");
    printf("Couleurs: 0:Rouge, 1:Vert, 2:Jaune, 3:Bleu, 4:Violet, 5:Orange\n");
    printf("Formes: O:Rond, C:Carre, L:Losange, E:Etoile, T:Trefle, X:Croix\n");
    printf("Saisir fin pour arreter la partie en cours\n");
}

// procedure pour affichier le menu principale
void afficher_menu_principal() {
    printf("\nQWIRKLE\n");
    printf("1. Nouvelle Partie\n");
    printf("2. Regles du jeu\n");
    printf("3. Voir les scores\n");
    printf("4. Quitter\n");
    printf("Votre choix : ");
}

// procedure pour afficher les règles
void afficher_regles() {
    printf("\nRègles du jeu\n");
    printf("Aligner des tuiles avec même couleur ou forme\n");
    printf("Une ligne ne peut pas avoir deux tuiles identiques cote à cote\n");
    printf("QWIRKLE si une ligne de 6 tuiles, rapporte 6 points\n");
    printf("Fin quand la pioche est vide et un joueur n'a plus de tuiles.\n");
}

// convertit un caractère saisi par le joueur en type énuméré forme pour indiquer la forme de la tuile
Forme char_vers_forme(char c) {
    switch(c) {
        case 'O':
            return ROND;
        case 'C':
            return CARRE;
        case 'L':
            return LOSANGE;
        case 'E':
            return ETOILE;
        case 'T':
            return TREFLE;
        case 'X':
            return CROIX;
        default:
            return VIDE_F;
    }
}

// sauvegarde le gagnant dans un fichier texte
void sauvegarder_score(char *pseudo, int score) {
    FILE *fichier = fopen("scores.txt", "a"); // "a" pour ajouter à la fin
    if (fichier != NULL) {
        // On écrit le nom et le score séparés par un espace
        fprintf(fichier, "%s %d\n", pseudo, score);
        fclose(fichier);
        printf("\nLe score est sauvegardé dans l'historique\n");
    } else {
        printf("\nImpossible de sauvegarder le score\n");
    }
}

// lis et affiche le fichier des scores
void lire_scores() {
    FILE *fichier = fopen("scores.txt", "r"); // "r" pour lire
    char nom[50];
    int score;

    printf("\nTableau des scores\n");
    if (fichier == NULL) {
        printf("Aucun score pour le moment\n");
        return;
    }

    // On lit tant qu'il y a des lignes (format : string int)
    while (fscanf(fichier, "%s %d", nom, &score) == 2) {
        printf("%-15s : %d points\n", nom, score);
    }

    fclose(fichier);
    printf("\n");
}