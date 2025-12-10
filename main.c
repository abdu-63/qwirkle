#include "structures.h"

int main() {
    srand(time(NULL)); // aléatoire grâce au temps actuelle
    int choix_menu = 0;

    // Boucle principale du menu
    while (choix_menu != 3) {
        afficher_menu_principal();

        // Lecture sécurisée du choix utilisateur
        if (scanf("%d", &choix_menu) != 1) {
            while(getchar() != '\n'); // nettoyage de la mémoire en cas de bug
            continue; // ignore le switch case et revient au while
        }

        switch (choix_menu) {
            case 1:
                lancer_partie();
                break;
            case 2:
                afficher_regles();
                break;
            case 3:
                printf("Au revoir\n");
                break;
            default:
                printf("Choix invalide\n");
        }
    }
    return 0;
}