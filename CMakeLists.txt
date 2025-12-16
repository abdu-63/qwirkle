cmake_minimum_required(VERSION 4.0)
project(qwirkle_v3 C)

set(CMAKE_C_STANDARD 11)

add_executable(qwirkle_v3 main.c
        structures.h
        plateau.c
        plateau.h
        joueur.c
        joueur.h
        affichage.c
        affichage.h
        regles.c
        regles.h
        jeu.c
        jeu.h)