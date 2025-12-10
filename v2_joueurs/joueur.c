#include "structures.h"

void init_pioche(Pioche *p, int mode_degrade) {
    p->mode = mode_degrade;
    int nb_copies = mode_degrade ? 1 : 3;
    p->nb_restantes = nb_copies * 6 * 6;

    int index = 0;
    for (int c = 0; c < 6; c++) {
        for (int f = 0; f < 6; f++) {
            for (int k = 0; k < nb_copies; k++) {
                p->tuiles[index].couleur = (Couleur)c;
                p->tuiles[index].forme = (Forme)f;
                index++;
            }
        }
    }

    // Mélange
    srand(time(NULL));
    for (int i = p->nb_restantes - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Tuile temp = p->tuiles[i];
        p->tuiles[i] = p->tuiles[j];
        p->tuiles[j] = temp;
    }
}

void completer_main(Joueur *j, Pioche *p) {
    for (int i = 0; i < 6; i++) {
        if (j->main[i].forme == VIDE_F) { // VIDE_F ou autre valeur par défaut ? VIDE_F est défini dans structures.h, mais il faut s'assurer qu'il est != des autres formes.
            // Ah, il faut initialiser la main avant d'appeler completer_main la première fois, ou s'assurer que structures.h a VIDE_F.
            // Oui, enum Forme a VIDE_F.
            if (p->nb_restantes > 0) {
                p->nb_restantes--;
                j->main[i] = p->tuiles[p->nb_restantes];
            }
        }
    }
}
