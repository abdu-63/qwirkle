#include "structures.h"

int main() {
    srand(time(NULL));
    Plateau plateau;
    Pioche pioche;
    Joueur joueurs[4];
    int nb_joueurs = 0;
    int tour = 0;

    init_plateau(&plateau);
    init_pioche(&pioche, 0);

    printf("Version 3 : Boucle de Jeu (Sans Validation de Regles)\n");
    
    while (nb_joueurs < 2 || nb_joueurs > 4) {
        printf("Nombre de joueurs (2 a 4) > ");
        if (scanf("%d", &nb_joueurs) != 1) { while(getchar() != '\n'); }
    }

    for (int i = 0; i < nb_joueurs; i++) {
        printf("Pseudo joueur %d: ", i+1);
        scanf("%s", joueurs[i].pseudo);
        joueurs[i].score = 0;
        for(int k=0; k<6; k++) {
            joueurs[i].main[k].forme = VIDE_F;
            joueurs[i].main[k].couleur = VIDE_C;
        }
        completer_main(&joueurs[i], &pioche);
    }

    // Boucle de jeu
    char buffer[20];
    int partie_en_cours = 1;

    while (partie_en_cours) {
        int id = tour % nb_joueurs;

        printf("\nAu tour de %s\n", joueurs[id].pseudo);
        afficher_plateau(plateau);
        afficher_main(joueurs[id]);

        printf("> (ex: ebC1, fin): ");
        scanf("%s", buffer);

        if (strcmp(buffer, "fin") == 0) {
            printf("Partie interrompue.\n");
            break;
        }

        if (strlen(buffer) < 4) {
            printf("Format invalide. Essayez: ligne colonne Forme Couleur (ex: ebC1)\n");
            continue;
        }

        int l = buffer[0] - 'a';
        int c = buffer[1] - 'a';
        Forme f = char_vers_forme(buffer[2]);
        Couleur col = buffer[3] - '0';

        if (f == VIDE_F || col < 0 || col > 5) {
             printf("Tuile invalide.\n");
             continue;
        }
        
        if (!est_dans_plateau(l, c)) {
            printf("Hors plateau !\n");
            continue;
        }

        if (possede_tuile(joueurs[id], f, col) == 0) {
            printf("Tuile non possedee !\n");
            continue;
        }

        // Pas de vérification de règles ici
        poser_tuile(&plateau, l, c, f, col);
        retirer_tuile_main(&joueurs[id], f, col);
        completer_main(&joueurs[id], &pioche);

        printf("Tuile posee.\n");
        tour++;
    }

    return 0;
}
