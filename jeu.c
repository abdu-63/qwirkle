#include "jeu.h"
#include "plateau.h"
#include "joueur.h"
#include "affichage.h"
#include "regles.h"

// sauvegarde la partie
void effectuer_sauvegarde(Plateau p, Pioche pi, Joueur js[], int nb, int tour, int prem) {
    FILE *f = fopen("save.bin", "wb"); // "wb" = write binary
    if (f == NULL) {
        printf("Erreur lors de la creation du fichier de sauvegarde\n");
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
    printf("\nPartie sauvegardée\n");
}

// reprend la partie sauvgardé
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

// fonction principale pour les parties
void lancer_partie(int reprendre) {
    Plateau plateau;
    Pioche pioche;
    Joueur joueurs[4];
    int nb_joueurs = 0;
    int tour = 0;
    int est_premier = 1;

    // initialiser la partie soit on charge une partie ou soit on en crée une
    if (reprendre) { // charge une partie
        if (!charger_sauvegarde(&plateau, &pioche, joueurs, &nb_joueurs, &tour, &est_premier)) {
            printf("\nAucune sauvegarde trouvée\n");
            printf("Retour au menu\n");
            return;
        }
        printf("\nPartie chargée. Au tour de %s \n", joueurs[tour % nb_joueurs].pseudo);
    }
    else {
        // création nouvelle partie
        int mode = -1; // choix du mode (normal, dégradé)
        printf("\nMode de jeu\n");
        printf("0. Normal (108 tuiles)\n");
        printf("1. Dégradé (36 tuiles)\n");
        while (mode != 0 && mode != 1) {
            printf("Choix : ");
            if (scanf("%d", &mode) != 1) { while(getchar() != '\n'); }
        }

        // choix du nombre de joueur
        while (nb_joueurs < 2 || nb_joueurs > 4) {
            printf("Nombre de joueurs (2 a 4) : ");
            if (scanf("%d", &nb_joueurs) != 1) { while(getchar() != '\n'); }
        }

        // initialisation du plateau et de la pioche
        init_plateau(&plateau); // initialise le plateau avec des case vide (avec pointeur)
        init_pioche(&pioche, mode); // prépare la pioche selon le mode choisi (avec pointeur)

        // saisie du noms des joueurs
        printf("\nNoms des joueurs\n");
        for (int i = 0; i < nb_joueurs; i++) {
            printf("Pseudo joueur %d: ", i+1);
            scanf("%s", joueurs[i].pseudo);
            joueurs[i].score = 0;
            for(int k=0; k<6; k++) joueurs[i].main[k].forme = VIDE_F;
            completer_main(&joueurs[i], &pioche);
        }
    }

    // boucle qui fait tourner le jeu
    char buffer[20];
    int partie_en_cours = 1;

    // si la partie est en cours
    while (partie_en_cours) {
        int id = tour % nb_joueurs;

        // test de fin de partie
        if (est_fin_partie(pioche, joueurs[id])) {
            printf("\nfin de la partie\n");
            joueurs[id].score += 6;
            partie_en_cours = 0;
            break;
        }

        // affiche la pioche et les pseudo des joueurs
        printf("\nAu tour de %s (Score: %d)\n", joueurs[id].pseudo, joueurs[id].score);
        printf("Pioche : %d tuiles\n", pioche.nb_restantes);

        // afficher maintenant le plateau et la main initialisé plus tôt
        afficher_plateau(plateau);
        afficher_main(joueurs[id]);

        printf(" (ex: ebC1, échange, sauver, fin): ");
        scanf("%s", buffer);

        // commandes autres que placer la tuile
        // commande "fin" quitte la partie
        if (strcmp(buffer, "fin") == 0) {
            printf("Partie interrompue\n");
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

        // commande "sauver" sauvegarde l'état actuel
        if (strcmp(buffer, "sauver") == 0) {
            effectuer_sauvegarde(plateau, pioche, joueurs, nb_joueurs, tour, est_premier);
            continue; // reste au même tour
        }

        // commande "echange" échange les tuiles avec ceux de la pioche
        if (strcmp(buffer, "échange") == 0) {
            echanger_tuiles(&joueurs[id], &pioche);
            tour++;
            continue;
        }

        if (strlen(buffer) < 4) continue;
        // conversion de la saisie "ebC1" en indices et types
        int l = buffer[0] - 'a'; // pour la ligne (lettre -> 0-11)
        int c = buffer[1] - 'a'; // pour la colonne (lettre -> 0-25)
        Forme f = char_vers_forme(buffer[2]); // pour la forme (lettre -> enum)
        Couleur col = buffer[3] - '0'; // pour la couleur (char '0'-'5' -> int)

        // vérification de la saisie
        if (f == VIDE_F || col < 0 || col > 5) continue;

        // vérifie si le joueur possède bien la tuile
        if (possede_tuile(joueurs[id], f, col) == 0) {
            printf("Tuile non possedée\n");
            continue;
        }

        // vérifie si le coup est légal selon les règles
        if (est_coup_valide(plateau, l, c, f, col, est_premier) == 0) continue;

        // application du coup et des points
        poser_tuile(&plateau, l, c, f, col);
        int pts = calculer_points(plateau, l, c);
        joueurs[id].score += pts;

        // mise à jour de la main et passage au tour suivant
        retirer_tuile_main(&joueurs[id], f, col);
        completer_main(&joueurs[id], &pioche);

        printf("Points marques : %d\n", pts);
        est_premier = 0;
        tour++;
    }

    // calcul gagnant après la fin
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
    // affiche le gagnant
    printf("Le vainqueur est %s !\n", joueurs[id_gagnant].pseudo);
    sauvegarder_score(joueurs[id_gagnant].pseudo, joueurs[id_gagnant].score);

    // supprimer le fichier de sauvegarde quand la partie est finie proprement pour pas poser de soucis a la prochaine fois
    remove("save.bin");
}