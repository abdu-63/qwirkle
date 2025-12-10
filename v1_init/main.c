#include "structures.h"

int main() {
    Plateau p;
    init_plateau(&p);
    
    printf("Version 1 : Initialisation et Affichage du Plateau\n");
    afficher_plateau(p);

    return 0;
}
