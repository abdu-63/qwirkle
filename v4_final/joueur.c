#include "structures.h"

void init_pioche(Pioche *p, int mode_degrade) {
    p->mode = mode_degrade;
    int nb_copies = mode_degrade ? 1 : 3;
    p->nb_restantes = nb_copies * 6 * 6; // 6 formes * 6 couleurs * nb_copies

    int index = 0;
    // Génération des tuiles
    for (int c = 0; c < 6; c++) {
        for (int f = 0; f < 6; f++) {
            for (int k = 0; k < nb_copies; k++) {
                p->tuiles[index].couleur = (Couleur)c;
                p->tuiles[index].forme = (Forme)f;
                index++;
            }
        }
    }

    // Mélange de Fisher-Yates pour randomiser la pioche
    for (int i = p->nb_restantes - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Tuile temp = p->tuiles[i];
        p->tuiles[i] = p->tuiles[j];
        p->tuiles[j] = temp;
    }
}

void completer_main(Joueur *j, Pioche *p) {
    for (int i = 0; i < 6; i++) {
        // Si l'emplacement est vide (VIDE_F), on pioche
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

// Retire une tuile spécifique de la main du joueur
void retirer_tuile_main(Joueur *j, Forme f, Couleur c) {
    for (int i = 0; i < 6; i++) {
        if (j->main[i].forme == f && j->main[i].couleur == c) {
            j->main[i].forme = VIDE_F;
            j->main[i].couleur = VIDE_C;
            return;
        }
    }
}

// Echange les tuiles de la main du joueur avec la pioche 
void echanger_tuiles(Joueur *j, Pioche *p) {
    if (p->nb_restantes == 0) {
        printf("Pioche vide !\n");
        return;
    }
    printf("Indices des tuiles a echanger (1-6), tapez 0 pour finir :\n");

    int choix;
    int nb_echanges = 0;

    // Boucle de sélection des tuiles à échanger
    while (1) {
        printf("> ");
        
        if (scanf("%d", &choix) != 1) {
            while(getchar() != '\n') {} // Nettoyage buffer
            continue;
        }

        if (choix == 0) break;

        if (choix >= 1 && choix <= 6) {
            int idx = choix - 1;
            if (j->main[idx].forme != VIDE_F) {
                // Remet la tuile dans la pioche
                p->tuiles[p->nb_restantes] = j->main[idx];
                p->nb_restantes++;
                
                // Marque l'emplacement en main comme vide
                j->main[idx].forme = VIDE_F;
                j->main[idx].couleur = VIDE_C;
                nb_echanges++;
            }
        }
    }

    // Si on a échangé, on remélange la pioche et on complète la main
    if (nb_echanges > 0) {
        for (int i = 0; i < p->nb_restantes; i++) {
            int r = rand() % p->nb_restantes;
            Tuile temp = p->tuiles[i];
            p->tuiles[i] = p->tuiles[r];
            p->tuiles[r] = temp;
        }
        completer_main(j, p); // Pioche les nouvelles tuiles
        printf("%d tuiles echangees.\n", nb_echanges);
    }
}