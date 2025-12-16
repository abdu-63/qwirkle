### 1. Règles du Jeu (Logique métier)
**Matériel et Initialisation :**
- **Plateau :** Grille de **12 lignes par 26 colonnes**.
- **Modes de jeu :**
    - _Normal :_ 108 tuiles (3 copies de chaque combinaison forme/couleur).
    - _Dégradé :_ 36 tuiles (1 seule copie de chaque combinaison).
- **Joueurs :** 2 à 4 joueurs.
- **Main du joueur :** Toujours **6 tuiles** (cachées aux adversaires).
- **Pioche :** Les tuiles sont tirées au hasard.
**Déroulement d'un tour :**
- Le joueur peut effectuer **une** action parmi trois :
    1. **Poser une tuile :** Sur une ligne ou colonne.
    2. **Poser plusieurs tuiles :** Elles doivent partager une caractéristique (forme ou couleur) et être alignées sur une seule ligne/colonne.
    3. **Échanger des tuiles :** Tout ou partie de sa main. Le joueur ne pose rien et passe son tour.
- À la fin de l'action, le joueur complète sa main pour avoir de nouveau 6 tuiles (si la pioche le permet).
**Règles de pose (Validité) :**
- **Connexité :** Les tuiles doivent toucher celles déjà présentes (sauf au premier tour).
- **Unicité de ligne :** Une ligne doit avoir une caractéristique commune (tous même couleur OU tous même forme).
- **Pas de doublon :** Une ligne ne peut pas contenir deux fois la même tuile (ex: pas deux carrés rouges dans la même ligne).
- **Taille max :** Une ligne ne peut pas dépasser 6 tuiles.
**Calcul des scores :**
- **Base :** 1 point par tuile dans la ligne créée ou complétée.
- **Croisement :** Une tuile compte pour 2 lignes (horizontale et verticale) si elle complète les deux.
- **Qwirkle :** Bonus de **+6 points** si on complète une ligne de 6 tuiles.
- **Fin de partie :** Bonus de **+6 points** pour le premier joueur qui vide sa main (si la pioche est vide).
**Fin de partie :**
- La partie s'arrête si la pioche est vide ET qu'un joueur a vidé sa main.
- Ou si la pioche est vide ET qu'aucun mouvement n'est possible.
- Ou si les joueurs décident d'arrêter à la fin d'un tour complet.
---
### 2. Contraintes Techniques (Implémentation)
**Interface et Affichage :**
- **Mode console** uniquement.
- **Symboles :** Utiliser des lettres majuscules (C, R, E, L, T, X) OU des symboles ANSI via des macros.
- **Couleurs :** 6 couleurs distinctes assurant un bon contraste.
- **Menu de démarrage :** Doit proposer : Règles, Nouvelle partie, Scores, Quitter (et Reprendre partie pour le bonus).
- **Affichage en jeu :** À chaque tour, afficher la zone de jeu, la main du joueur et son score total.
**Saisie des coups (Input) :**
- Format obligatoire : `ligne colonne Forme Couleur` (ex: `ebC1`).
    - Coordonnées en minuscules.
    - Forme en majuscule.
    - Couleur en chiffre.
- Pour plusieurs tuiles, enchaîner les saisies avant de valider.
- Gérer les mauvaises saisies utilisateur.
**Niveau de vérification (Base vs Bonus) :**
- **Pour le jeu de base :** L'ordinateur ne valide PAS strictement le coup. Il vérifie juste : possession de la tuile, connexité, et alignement (ligne/colonne unique). En cas d'erreur basique, on rejoue.
- **Pour le Bonus (+3 pts) :** L'ordinateur doit rejeter tout coup invalide selon les règles officielles du Qwirkle.
---
### 3. Normes de Code (Qualité)
Ces points sont cruciaux pour la notation :
- **Pas de variables globales**.
- **Séparation Données/Affichage :** Ne pas modifier les tableaux/données à l'intérieur d'une fonction d'affichage (`printf`).
- **Cross-platform :** Ne pas utiliser de librairies spécifiques à un OS (ex: pas de `<windows.h>` ou `win.h`).
- **Pas de duplication de code**.
- **Passage par adresse :** Uniquement lorsque c'est nécessaire.
- **Macros :** À utiliser si vous employez la table ANSI étendue.
---
### 4. Fonctionnalités Bonus (Optionnelles pour points supplémentaires)
Si vous visez la note maximale, vérifiez la présence de ces éléments 
1. **Validation stricte des règles** (+3 points).
2. **Sauvegarde / Chargement :** Possibilité de sauvegarder et quitter, puis reprendre au menu.
3. **High Scores :** Sauvegarde des 10 meilleurs scores dans un fichier.
4. **Échange partiel :** Possibilité de n'échanger que certaines tuiles au lieu de toute la main.