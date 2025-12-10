#include "structures.h"

void lancer_partie() {
    // 1. Configuration du mode de jeu
    int mode = -1;
    printf("\nMode de jeu\n");
    printf("0. Normal (108 tuiles, 3 copies)\n");
    printf("1. Degrade (36 tuiles, 1 copie)\n");
    while (mode != 0 && mode != 1) {
        printf("Choix (0 ou 1) > ");
        if (scanf("%d", &mode) != 1) { while(getchar() != '\n'); }
    }

    // 2. Configuration du nombre de joueurs (2 à 4)
    int nb_joueurs = 0;
    while (nb_joueurs < 2 || nb_joueurs > 4) {
        printf("Nombre de joueurs (2 a 4) > ");
        if (scanf("%d", &nb_joueurs) != 1) { while(getchar() != '\n'); } // Nettoyage buffer
    }

    Plateau plateau;
    Pioche pioche;
    Joueur joueurs[4];

    init_plateau(&plateau);
    init_pioche(&pioche, mode);

    printf("\nNoms des joueurs\n");
    for (int i = 0; i < nb_joueurs; i++) {
        printf("Pseudo joueur %d: ", i+1);
        scanf("%s", joueurs[i].pseudo);
        joueurs[i].score = 0;
        for(int k=0; k<6; k++) joueurs[i].main[k].forme = VIDE_F;
        completer_main(&joueurs[i], &pioche);
    }

    // 3. Boucle principale du jeu
    // Alterne entre les joueurs jusqu'à la fin de la partie
    int tour = 0;
    int est_premier = 1; // Marqueur spécial pour le tout premier tour (règles assouplies)
    char buffer[20];
    int partie_en_cours = 1;

    while (partie_en_cours) {
        int id = tour % nb_joueurs; // Index du joueur courant (0, 1, 2, ou 3)

        // Vérification de la condition de fin de partie
        if (est_fin_partie(pioche, joueurs[id])) {
            printf("\nFin de la partie\n");
            joueurs[id].score += 6; // Bonus fin
            partie_en_cours = 0;
            break;
        }

        printf("\nAu tour de %s (Score: %d)\n", joueurs[id].pseudo, joueurs[id].score);
        printf("Pioche : %d tuiles\n", pioche.nb_restantes);

        afficher_plateau(plateau);
        afficher_main(joueurs[id]);

        // Demande d'action au joueur
        printf("> (ex: ebC1, echange, fin): ");
        scanf("%s", buffer);

        // Gestion de l'interruption volontaire
        if (strcmp(buffer, "fin") == 0) {
            printf("Partie interrompue.\n");
            return; // Quitte la fonction et revient au menu
        }

        // Gestion de l'action 'echange'
        // Le joueur échange sa main contre de nouvelles tuiles et passe son tour
        if (strcmp(buffer, "echange") == 0) {
            echanger_tuiles(&joueurs[id], &pioche);
            tour++;
            continue;
        }

        if (strlen(buffer) < 4) continue;
        int l = buffer[0] - 'a';
        int c = buffer[1] - 'a';
        Forme f = char_vers_forme(buffer[2]);
        Couleur col = buffer[3] - '0';

        if (f == VIDE_F || col < 0 || col > 5) continue;

        if (possede_tuile(joueurs[id], f, col) == 0) {
            printf("Tuile non possedee !\n");
            continue;
        }

        // Validation du coup proposé
        // Vérifie si le coup respecte les règles du Qwirkle
        if (est_coup_valide(plateau, l, c, f, col, est_premier) == 0) continue;

        // Action
        poser_tuile(&plateau, l, c, f, col);
        int pts = calculer_points(plateau, l, c);
        joueurs[id].score += pts;

        retirer_tuile_main(&joueurs[id], f, col);
        completer_main(&joueurs[id], &pioche);

        printf(">>> Points marques : %d\n", pts);
        est_premier = 0;
        tour++;
    }

    // Affichage des scores finaux
    printf("\nResultats\n");
    int max_score = -1;
    int id_gagnant = -1;

    for(int i=0; i < nb_joueurs; i++) {
        printf("%s : %d points\n", joueurs[i].pseudo, joueurs[i].score);
        if (joueurs[i].score > max_score) {
            max_score = joueurs[i].score;
            id_gagnant = i;
        }
    }
    printf("Le vainqueur est %s \n", joueurs[id_gagnant].pseudo);
}