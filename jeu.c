#include "structures.h"

// --- Fonctions utilitaires pour la sauvegarde ---

void effectuer_sauvegarde(Plateau p, Pioche pi, Joueur js[], int nb, int tour, int prem) {
    FILE *f = fopen("save.bin", "wb"); // "wb" = write binary
    if (f == NULL) {
        printf("Erreur lors de la creation du fichier de sauvegarde.\n");
        return;
    }

    Sauvegarde s;
    s.plateau = p;
    s.pioche = pi;
    // Copie des joueurs
    for(int i=0; i<4; i++) s.joueurs[i] = js[i];
    s.nb_joueurs = nb;
    s.tour = tour;
    s.est_premier = prem;

    fwrite(&s, sizeof(Sauvegarde), 1, f);
    fclose(f);
    printf("\n>>> PARTIE SAUVEGARDEE AVEC SUCCES ! <<<\n");
}

int charger_sauvegarde(Plateau *p, Pioche *pi, Joueur js[], int *nb, int *tour, int *prem) {
    FILE *f = fopen("save.bin", "rb"); // "rb" = read binary
    if (f == NULL) return 0; // Pas de sauvegarde trouvée

    Sauvegarde s;
    if (fread(&s, sizeof(Sauvegarde), 1, f) != 1) {
        fclose(f);
        return 0; // Erreur lecture
    }

    *p = s.plateau;
    *pi = s.pioche;
    for(int i=0; i<4; i++) js[i] = s.joueurs[i];
    *nb = s.nb_joueurs;
    *tour = s.tour;
    *prem = s.est_premier;

    fclose(f);
    return 1; // Succès
}

// --- Fonction Principale ---

void lancer_partie(int reprendre) {
    Plateau plateau;
    Pioche pioche;
    Joueur joueurs[4];
    int nb_joueurs = 0;
    int tour = 0;
    int est_premier = 1;

    // INITIALISATION : Soit on charge, soit on crée
    if (reprendre) {
        if (!charger_sauvegarde(&plateau, &pioche, joueurs, &nb_joueurs, &tour, &est_premier)) {
            printf("\nAucune sauvegarde trouvee ou fichier corrompu.\n");
            printf("Retour au menu...\n");
            return;
        }
        printf("\n>>> Partie chargee ! Au tour de %s <<<\n", joueurs[tour % nb_joueurs].pseudo);
    }
    else {
        // --- Création nouvelle partie (Code d'avant) ---
        int mode = -1;
        printf("\n--- MODE DE JEU ---\n");
        printf("0. Normal (108 tuiles)\n");
        printf("1. Degrade (36 tuiles)\n");
        while (mode != 0 && mode != 1) {
            printf("Choix > ");
            if (scanf("%d", &mode) != 1) { while(getchar() != '\n'); }
        }

        while (nb_joueurs < 2 || nb_joueurs > 4) {
            printf("Nombre de joueurs (2 a 4) > ");
            if (scanf("%d", &nb_joueurs) != 1) { while(getchar() != '\n'); }
        }

        init_plateau(&plateau);
        init_pioche(&pioche, mode);

        printf("\n--- NOMS DES JOUEURS ---\n");
        for (int i = 0; i < nb_joueurs; i++) {
            printf("Pseudo joueur %d: ", i+1);
            scanf("%s", joueurs[i].pseudo);
            joueurs[i].score = 0;
            for(int k=0; k<6; k++) joueurs[i].main[k].forme = VIDE_F;
            completer_main(&joueurs[i], &pioche);
        }
    }

    // --- BOUCLE DE JEU ---
    char buffer[20];
    int partie_en_cours = 1;

    while (partie_en_cours) {
        int id = tour % nb_joueurs;

        if (est_fin_partie(pioche, joueurs[id])) {
            printf("\n!!! FIN DE LA PARTIE !!!\n");
            joueurs[id].score += 6;
            partie_en_cours = 0;
            break;
        }

        printf("\nAu tour de %s (Score: %d)\n", joueurs[id].pseudo, joueurs[id].score);
        printf("Pioche : %d tuiles\n", pioche.nb_restantes);

        afficher_plateau(plateau);
        afficher_main(joueurs[id]);

        printf("> (ex: ebC1, echange, sauver, fin): ");
        scanf("%s", buffer);

        // --- COMMANDES SPECIALES ---

        if (strcmp(buffer, "fin") == 0) {
            printf("Partie interrompue.\n");
            // Sauvegarde du score (votre code précédent)
             int max_temp = -1;
            int id_temp = -1;
            for(int i=0; i < nb_joueurs; i++) {
                if (joueurs[i].score > max_temp) {
                    max_temp = joueurs[i].score;
                    id_temp = i;
                }
            }
            if (id_temp != -1) sauvegarder_score(joueurs[id_temp].pseudo, joueurs[id_temp].score);
            return;
        }

        // AJOUT : Commande pour sauvegarder l'état
        if (strcmp(buffer, "sauver") == 0) {
            effectuer_sauvegarde(plateau, pioche, joueurs, nb_joueurs, tour, est_premier);
            continue; // On reste au même tour
        }

        if (strcmp(buffer, "echange") == 0) {
            echanger_tuiles(&joueurs[id], &pioche);
            tour++;
            continue;
        }

        // --- LOGIQUE DE JEU CLASSIQUE ---
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

        if (est_coup_valide(plateau, l, c, f, col, est_premier) == 0) continue;

        poser_tuile(&plateau, l, c, f, col);
        int pts = calculer_points(plateau, l, c);
        joueurs[id].score += pts;

        retirer_tuile_main(&joueurs[id], f, col);
        completer_main(&joueurs[id], &pioche);

        printf(">>> Points marques : %d\n", pts);
        est_premier = 0;
        tour++;
    }

    // Fin de partie : Calcul gagnant
    printf("\nRésultat\n");
    int max_score = -1;
    int id_gagnant = -1;
    for(int i=0; i < nb_joueurs; i++) {
        printf("%s : %d points\n", joueurs[i].pseudo, joueurs[i].score);
        if (joueurs[i].score > max_score) {
            max_score = joueurs[i].score;
            id_gagnant = i;
        }
    }
    printf("LE VAINQUEUR EST %s !\n", joueurs[id_gagnant].pseudo);
    sauvegarder_score(joueurs[id_gagnant].pseudo, joueurs[id_gagnant].score);

    // Optionnel : Supprimer le fichier de sauvegarde quand la partie est finie proprement
    remove("save.bin");
}