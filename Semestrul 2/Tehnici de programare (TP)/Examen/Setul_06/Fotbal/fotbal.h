#ifndef __FOTBAL_H
#define __FOTBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct JUCATOR *Jucator_t;

typedef struct ECHIPA *Echipa_t;

typedef struct CAMPIONAT *Campionat_t;

//functii de creare aditionale

Jucator_t create_player(char *nume, int salariu);

Echipa_t create_team(const char *name);

Campionat_t create_championship(const char *name);

//functii de printare aditionale

void printPlayer(Jucator_t player);

void printTeam(Echipa_t team);

void printChampionship(Campionat_t championship);

//functii de free aditionale
void freePlayer(Jucator_t player);

void freeTeam(Echipa_t team);

void freeChampionship(Campionat_t championship);

//cerinta

Echipa_t addPlayer(Echipa_t team, Jucator_t player_to_add, Campionat_t champ);

Campionat_t addTeam(Campionat_t championship, Echipa_t team);

Jucator_t searchFootballPlayerInFootbalTeam(char *name, Echipa_t team);

Jucator_t searchFootballPlayerInFootbalChampionship(char *name, Campionat_t championship);

#endif