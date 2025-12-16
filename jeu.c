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
    for (int i = 0; i < 4; i++) {
        s.joueurs[i] = js[i];
    }
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
    for (int i = 0; i < 4; i++) {
        js[i] = s.joueurs[i];
    }
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
            for (int k = 0; k < 6; k++) {
                joueurs[i].main[k].forme = VIDE_F;
            }
            completer_main(&joueurs[i], &pioche);
        }
    }

    // boucle qui fait tourner le jeu
    char buffer[20];
    int partie_en_cours = 1;
    
    // variables pour le multi-coup
    Coup coups_en_cours[6];
    int nb_coups_en_cours = 0;
    int tuiles_utilisees[6] = {0};


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

        // Afficher seulement si aucun coup en cours
        if (nb_coups_en_cours == 0) {
            printf("\nAu tour de %s (Score: %d)\n", joueurs[id].pseudo, joueurs[id].score);
            printf("Pioche : %d tuiles\n", pioche.nb_restantes);
            afficher_plateau(plateau);
            afficher_main(joueurs[id]);
            printf(" (ex: ebC1, valider, échange, sauver, fin): ");
        } else {
            printf("Coup suivant : ");
        }
        scanf("%s", buffer);

        if (strcmp(buffer, "fin") == 0) {
            printf("Partie interrompue\n");
            int max_temp = -1;
            int id_temp = -1;
            for(int i=0; i < nb_joueurs; i++) {
                if (joueurs[i].score > max_temp) {
                    max_temp = joueurs[i].score;
                    id_temp = i;
                }
            }
            sauvegarder_derniere_partie(joueurs, nb_joueurs);
            if (id_temp != -1) sauvegarder_score(joueurs[id_temp].pseudo, joueurs[id_temp].score);
            return;
        }

        if (strcmp(buffer, "sauver") == 0) {
            effectuer_sauvegarde(plateau, pioche, joueurs, nb_joueurs, tour, est_premier);
            continue; 
        }

        if (strcmp(buffer, "échange") == 0) {
            if (nb_coups_en_cours > 0) {
                printf("Veuillez valider vos coups avant d'echanger\n");
                continue;
            }
            echanger_tuiles(&joueurs[id], &pioche);
            tour++;
            continue;
        }


        if (strcmp(buffer, "valider") == 0 || strcmp(buffer, "jouer") == 0) {
            if (nb_coups_en_cours == 0) {
                printf("Aucun coup à jouer\n");
                continue;
            }

            if (valider_serie_coups(plateau, coups_en_cours, nb_coups_en_cours, est_premier)) {
                // calcul score
                int pts = calculer_score_serie_coups(plateau, coups_en_cours, nb_coups_en_cours);
                joueurs[id].score += pts;
                printf("Points marques : %d (Total: %d)\n", pts, joueurs[id].score);

                // appliquer sur le vrai plateau et retirer de la main
                for (int k = 0; k < nb_coups_en_cours; k++) {
                    poser_tuile(&plateau, coups_en_cours[k].lig, coups_en_cours[k].col, coups_en_cours[k].forme, coups_en_cours[k].couleur);
                    retirer_tuile_main(&joueurs[id], coups_en_cours[k].forme, coups_en_cours[k].couleur);
                }
                
                completer_main(&joueurs[id], &pioche);
                est_premier = 0;
                tour++;
                nb_coups_en_cours = 0;
                for (int k = 0; k < 6; k++) {
                    tuiles_utilisees[k] = 0;
                }
            } else {
                 printf("Série de coups invalide, coups annulés\n");
                 nb_coups_en_cours = 0;
                 for (int k = 0; k < 6; k++) {
                     tuiles_utilisees[k] = 0;
                 }
            }
            continue;
        }

        if (strlen(buffer) < 4) continue;
        
        // Traitement d'un coup (ajout à la liste)
        if (nb_coups_en_cours >= 6) {
            printf("Max 6 tuiles par tour !\n");
            continue;
        }

        int l = buffer[0] - 'a'; 
        int c = buffer[1] - 'a'; 
        Forme f = char_vers_forme(buffer[2]); 
        Couleur col = buffer[3] - '0'; 

        if (f == VIDE_F || col < 0 || col > 5) continue;

        // Vérifier possession (en tenant compte de tuiles_utilisees)
        int index_trouve = -1;
        for (int k=0; k<6; k++) {
            if (!tuiles_utilisees[k] && joueurs[id].main[k].forme == f && joueurs[id].main[k].couleur == col) {
                index_trouve = k;
                break;
            }
        }

        if (index_trouve == -1) {
            printf("%s: Tuile non possedée (ou déjà utilisée ce tour)\n", buffer);
            continue;
        }

        // Ajout à la liste
        coups_en_cours[nb_coups_en_cours].lig = l;
        coups_en_cours[nb_coups_en_cours].col = c;
        coups_en_cours[nb_coups_en_cours].forme = f;
        coups_en_cours[nb_coups_en_cours].couleur = col;
        
        tuiles_utilisees[index_trouve] = 1;
        nb_coups_en_cours++;
        printf("%s: Coup ajoutée \n", buffer);

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
    sauvegarder_derniere_partie(joueurs, nb_joueurs);
    sauvegarder_score(joueurs[id_gagnant].pseudo, joueurs[id_gagnant].score);

    // supprimer le fichier de sauvegarde quand la partie est finie proprement pour pas poser de soucis a la prochaine fois
    remove("save.bin");
}