#include "structures.h"

int main() {
    srand(time(NULL));
    Plateau plateau;
    Pioche pioche;
    Joueur joueurs[4];
    int nb_joueurs = 0;

    init_plateau(&plateau);
    init_pioche(&pioche, 0); // Mode normal

    printf("Version 2 : Joueurs et Pioche\n");
    
    while (nb_joueurs < 2 || nb_joueurs > 4) {
        printf("Nombre de joueurs (2 a 4) > ");
        if (scanf("%d", &nb_joueurs) != 1) { while(getchar() != '\n'); }
    }

    for (int i = 0; i < nb_joueurs; i++) {
        printf("Pseudo joueur %d: ", i+1);
        scanf("%s", joueurs[i].pseudo);
        joueurs[i].score = 0;
        // Init main à vide important avant de compléter
        for(int k=0; k<6; k++) {
            joueurs[i].main[k].forme = VIDE_F;
            joueurs[i].main[k].couleur = VIDE_C;
        }
        completer_main(&joueurs[i], &pioche);
    }

    printf("\n--- Etat Initial ---\n");
    afficher_plateau(plateau);
    
    printf("\n--- Mains des Joueurs ---\n");
    for (int i = 0; i < nb_joueurs; i++) {
        afficher_main(joueurs[i]);
    }
    
    printf("\nPioche restante : %d tuiles\n", pioche.nb_restantes);

    return 0;
}
