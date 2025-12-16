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

void afficher_plateau(Plateau p) {
    // affiche les lettres des colonnes
    printf("   ");
    for (int j = 0; j < COLONNES; j++) {
        printf("%c ", 'a' + j);
    }
    printf("\n");
    // boucle des lignes
    for (int i = 0; i < LIGNES; i++) {
        printf("%c  ", 'a' + i);
        // boucle des colonnes
        for (int j = 0; j < COLONNES; j++) {
            Tuile t = p.grille[i][j];
            // affiche la case vide
            if (t.forme == VIDE_F) {
                printf(". ");
            } else {
                // %s = couleur, %c la forme ex: X, %s désactive la couleur,
                printf("%s%c%s ", get_color_code(t.couleur), get_char_forme(t.forme), COLOR_RESET);
            }
        }
        printf("\n");
    }
}

void afficher_main(Joueur j) {
    printf("Main de %s : ", j.pseudo);
    for (int i = 0; i < 6; i++) {
        Tuile t = j.main[i];
        if (t.forme != VIDE_F) {
            // %s = couleur, %c la forme ex: X, %d le numéro de la couleur, %s désactive la couleur,
            printf("[%s%c%d%s] ", get_color_code(t.couleur), get_char_forme(t.forme), t.couleur, COLOR_RESET);
        }
    }
    printf("\n");
}

void afficher_regles_saisie() {
    printf("Format : ligne colonne Forme Couleur (ex: ebC1)\n");
    printf("Couleurs: 0:Rouge, 1:Vert, 2:Jaune, 3:Bleu, 4:Violet, 5:Orange\n");
    printf("Formes: O:Rond, C:Carre, L:Losange, E:Etoile, T:Trefle, X:Croix\n");
    printf("Saisir fin pour arreter la partie en cours\n");
}

void afficher_menu_principal() {
    printf("\nQWIRKLE\n");
    printf("1. Nouvelle Partie\n");
    printf("2. Regles du jeu\n");
    printf("3. Voir les scores\n");
    printf("4. Quitter\n");
    printf("Votre choix : ");
}

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
        case 'o':
            return ROND;
        case 'C':
        case 'c':
            return CARRE;
        case 'L':
        case 'l':
            return LOSANGE;
        case 'E':
        case 'e':
            return ETOILE;
        case 'T':
        case 't':
            return TREFLE;
        case 'X':
        case 'x':
            return CROIX;
        default:
            return VIDE_F;
    }
}

// sauvegarde le gagnant dans un fichier texte
void sauvegarder_score(char *pseudo, int score) {
    FILE *fichier = fopen("scores.txt", "a"); // "a" pour ajouter à la fin
    if (fichier != NULL) {
        fprintf(fichier, "%s %d\n", pseudo, score);
        fclose(fichier);
        printf("\nLe score est sauvegardé dans l'historique\n");
    } else {
        printf("\nImpossible de sauvegarder le score\n");
    }
}

void lire_scores() {
    FILE *fichier = fopen("scores.txt", "r"); // "r" pour lire
    char nom[50];
    int score;

    printf("\nMeilleurs scores\n");
    if (fichier == NULL) {
        printf("Aucun score pour le moment\n");
        return;
    }

    while (fscanf(fichier, "%s %d", nom, &score) == 2) {
        printf("%-15s : %d points\n", nom, score);
    }

    fclose(fichier);
    printf("\n");
}

void sauvegarder_derniere_partie(Joueur joueurs[], int nb_joueurs) {
    FILE *fichier = fopen("derniere_partie.txt", "w"); // "w" pour écraser
    if (fichier != NULL) {
        for (int i = 0; i < nb_joueurs; i++) {
            fprintf(fichier, "%s %d\n", joueurs[i].pseudo, joueurs[i].score);
        }
        fclose(fichier);
    }
}

void lire_derniere_partie() {
    FILE *fichier = fopen("derniere_partie.txt", "r");
    char nom[50];
    int score;

    printf("\nScores de la dernière partie\n");
    if (fichier == NULL) {
        printf("Aucune partie jouée récemment\n");
        return;
    }

    while (fscanf(fichier, "%s %d", nom, &score) == 2) {
        printf("%-15s : %d points\n", nom, score);
    }

    fclose(fichier);
    printf("\n");
}