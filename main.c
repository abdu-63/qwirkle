#include "structures.h"

int main() {
    srand(time(NULL)); // aléatoire grâce au temps actuelle
    int choix_menu = 0;

    while (choix_menu != 3) {
        afficher_menu_principal();

        // Sécurisation de la saisie menu
        if (scanf("%d", &choix_menu) != 1) {
            while(getchar() != '\n');
            continue;
        }

        switch (choix_menu) {
            case 1:
                lancer_partie(); // Tout le jeu se passe ici
                break;
            case 2:
                afficher_regles();
                break;
            case 3:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    }
    return 0;
}