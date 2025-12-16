#include "joueur.h"

// initialise la pioche avec toutes les combinaison des tuiles par rapport au mode choisie
void init_pioche(Pioche *p, int mode_degrade) {
    p->mode = mode_degrade;
    int nb_copies;
    if (mode_degrade == 1) {
        nb_copies = 1;
    } else {
        nb_copies = 3;
    }
    p->nb_restantes = nb_copies * 6 * 6; // nombre de tuiles dans la pioche

    int index = 0;
    for (int c = 0; c < 6; c++) { // couleurs
        for (int f = 0; f < 6; f++) { // formes
            for (int k = 0; k < nb_copies; k++) { // copies (modes)
                p->tuiles[index].couleur = (Couleur)c;
                p->tuiles[index].forme = (Forme)f;
                index++;
            }
        }
    }

    // mélange de "Fisher-Yates"
    for (int i = p->nb_restantes - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Tuile temp = p->tuiles[i];
        p->tuiles[i] = p->tuiles[j];
        p->tuiles[j] = temp;
    }
}

void completer_main(Joueur *j, Pioche *p) {
    for (int i = 0; i < 6; i++) {
        if (j->main[i].forme == VIDE_F) { // test si l'emplacement de la main est vide
            if (p->nb_restantes > 0) {
                p->nb_restantes--;
                j->main[i] = p->tuiles[p->nb_restantes];
            }
        }
    }
}

int possede_tuile(Joueur j, Forme f, Couleur c) { // vérifie que le joueur a la tuile avant de la poser
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

void echanger_tuiles(Joueur *j, Pioche *p) {
    if (p->nb_restantes == 0) { // test si pioche vide avant d'échanger
        printf("Pioche vide\n");
        return;
    }
    printf("Tapez la tuile à échanger (1-6) et tapez 0 pour finir :\n");
    int choix;
    int nb_echanges = 0;
    while (1) {
        printf(": ");
        if (scanf("%d", &choix) != 1) { // lis et test si l'utilisateur tape une erreur ex: bonjour au lieu de 1
            while(getchar() != '\n'); // corrige l'érreur en supprimant bonjour et redemande pour pas crash
            continue;
        }
        if (choix == 0)
            break;
        if (choix >= 1 && choix <= 6) {
            int idx = choix - 1;
            if (j->main[idx].forme != VIDE_F) {
                p->tuiles[p->nb_restantes] = j->main[idx]; // remet la tuile dans la pioche
                p->nb_restantes++;
                // marque l'emplacement en main comme vide
                j->main[idx].forme = VIDE_F;
                j->main[idx].couleur = VIDE_C;
                nb_echanges++;
            }
        }
    }
    if (nb_echanges > 0) {
        for (int i = 0; i < p->nb_restantes; i++) {
            int r = rand() % p->nb_restantes;  // re mélange la pioche
            Tuile temp = p->tuiles[i];
            p->tuiles[i] = p->tuiles[r];
            p->tuiles[r] = temp;
        }
        completer_main(j, p);
        printf("%d tuiles échangées.\n", nb_echanges);
    }
}