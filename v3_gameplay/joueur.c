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
        if (j->main[i].forme == VIDE_F) {
            if (p->nb_restantes > 0) {
                p->nb_restantes--;
                j->main[i] = p->tuiles[p->nb_restantes];
            }
        }
    }
}

int possede_tuile(Joueur j, Forme f, Couleur c) {
    for (int i = 0; i < 6; i++) {
        if (j.main[i].forme == f && j.main[i].couleur == c) {
            return 1;
        }
    }
    return 0;
}

void retirer_tuile_main(Joueur *j, Forme f, Couleur c) {
    for (int i = 0; i < 6; i++) {
        if (j->main[i].forme == f && j->main[i].couleur == c) {
            j->main[i].forme = VIDE_F;
            j->main[i].couleur = VIDE_C;
            return;
        }
    }
}
