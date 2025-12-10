#include "structures.h"

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

void afficher_plateau(Plateau p) {
    printf("   ");
    for (int j = 0; j < COLONNES; j++) {
        printf("%c ", 'a' + j);
    }
    printf("\n");

    for (int i = 0; i < LIGNES; i++) {
        printf("%c  ", 'a' + i);
        for (int j = 0; j < COLONNES; j++) {
            Tuile t = p.grille[i][j];
            if (t.forme == VIDE_F) {
                printf(". ");
            } else {
                printf("%s%c%s ", get_color_code(t.couleur), get_char_forme(t.forme), COLOR_RESET);
            }
        }
        printf("\n");
    }
}
