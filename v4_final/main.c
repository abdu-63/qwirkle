#include "structures.h"

int main() {
    srand(time(NULL)); // aléatoire grâce au temps actuelle
    int choix_menu = 0;

    while (choix_menu != 5) { // On passe à 5 options
        printf("\nQWIRKLE\n");
        printf("1. Nouvelle Partie\n");
        printf("2. Reprendre partie\n"); // NOUVEAU
        printf("3. Regles du jeu\n");
        printf("4. Voir les scores\n");
        printf("5. Quitter\n");
        printf("Votre choix > ");

        if (scanf("%d", &choix_menu) != 1) {
            while(getchar() != '\n'); // nettoyage de la mémoire en cas de bug
            continue; // ignore le switch case et revient au while
        }

        switch (choix_menu) {
            case 1:
                lancer_partie(0); // 0 = Nouvelle partie
                break;
            case 2:
                lancer_partie(1); // 1 = Reprendre sauvegarde
                break;
            case 3:
                afficher_regles();
                break;
            case 4:
                lire_scores();
                break;
            case 5:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    }
    return 0;
}