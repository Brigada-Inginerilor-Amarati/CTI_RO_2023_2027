#include "fotbal.h"

#define MAX_LEN 50
#define PLAYERS_CAP 26
#define TEAM_CAP 20

struct JUCATOR{
    char name[MAX_LEN];
    int salary;
};

struct ECHIPA{
    char team_name[MAX_LEN];
    Jucator_t *players;
    int player_count;
};

struct CAMPIONAT{
    char championship_name[MAX_LEN];
    Echipa_t *teams;
    int team_count;
};

// Initializare

Jucator_t create_player(char *nume, int salariu){

    Jucator_t player = malloc(sizeof(struct JUCATOR));

    if(player == NULL){
        printf("eroare la alocarea dinamica jucator\n");
        return NULL;
    }

    strcpy(player->name, nume);
    player->salary = salariu;

    return player;

}

Echipa_t create_team(const char *name){
    Echipa_t team = malloc(sizeof(struct ECHIPA));

    if(team == NULL){
        printf("eroare alocare memorie echipa\n");
        return NULL;
    }

    strcpy(team->team_name, name);
    team->player_count = 0;

    team->players = malloc(PLAYERS_CAP * sizeof(Jucator_t));

    if(team->players == NULL){
        printf("eroare alocare memorie jucatori\n");
        free(team);
        return NULL;
    }

    return team;
}

Campionat_t create_championship(const char *name){
    Campionat_t championship = malloc(sizeof(struct CAMPIONAT));

    if(championship == NULL){
        printf("eroare alocare memorie campionat \n");
        return NULL;
    }

    strcpy(championship->championship_name, name);
    championship->team_count = 0;

    championship->teams = malloc(TEAM_CAP * sizeof(Campionat_t));

    if(championship->teams == NULL){
        printf("eroare alocare memorie echipe\n");
        free(championship);
        return NULL;
    }

    return championship;
}

void printPlayer(Jucator_t player){
    if(player != NULL){
        printf("Nume : %s - Salariu : %d \n", player->name, player->salary);
    }
}

void printTeam(Echipa_t team){
    if(team != NULL){
        printf("Echipa %s are urmatorii jucatori: \n", team->team_name);

        for(int i = 0; i < team->player_count; i++){
            printPlayer(team->players[i]);
        }
    }
}

void printChampionship(Campionat_t championship){
    if(championship != NULL){
        printf("Campionatul %s are urmatoare echipe: \n", championship->championship_name);

        for(int i = 0; i < championship->team_count; i++){
            printTeam(championship->teams[i]);
            printf("\n");
        }
    }
}

void freePlayer(Jucator_t player){
    if(player != NULL){
        free(player);
    }
}

void freeTeam(Echipa_t team){
    if(team != NULL){
        for(int i = 0; i < team->player_count; i++){
            freePlayer(team->players[i]);
        }
        free(team->players);
        free(team);
    }
}

void freeChampionship(Campionat_t championship){
    if(championship != NULL){
        for(int i = 0; i < championship->team_count; i++){
            freeTeam(championship->teams[i]);
        }
        free(championship->teams);
        free(championship);
    }
}

Jucator_t searchFootballPlayerInFootbalTeam(char *name, Echipa_t team){
    for(int i = 0; i < team->player_count; i++){
        if(strcmp(team->players[i]->name, name) == 0){
            return team->players[i];
        }
    }

    return NULL;
}

//timp O(m * n) m - nr echipe, n -nr jucatori/echipa
Jucator_t searchFootballPlayerInFootbalChampionship(char *name, Campionat_t championship){
    for(int i = 0; i < championship->team_count; i++){
        Jucator_t player = searchFootballPlayerInFootbalTeam(name, championship->teams[i]);

        if(player != NULL){
            return player;
        }
    }

    return NULL;
}

int existPlayer(Jucator_t player, Campionat_t champ){
    if(searchFootballPlayerInFootbalChampionship(player->name, champ)){
        return 0;
    }
    return 1;
}



Echipa_t addPlayer(Echipa_t team, Jucator_t player_to_add, Campionat_t champ){
    if(team->player_count < PLAYERS_CAP && existPlayer(player_to_add, champ)){
        if (player_to_add == NULL)
        {
            printf("eroare creare jucator\n");
            return NULL;
        }

        team->players[team->player_count++] = player_to_add;
    }
    else if(!existPlayer(player_to_add, champ)){
        printf("Jucatorul exista deja in echipa\n");
        freePlayer(player_to_add);
    }
    else{
        printf("Echipa este completa.\n");
    }

    return team;
}

Campionat_t addTeam(Campionat_t championship, Echipa_t team_to_add){
    if(championship->team_count < TEAM_CAP){
        if(team_to_add == NULL){
            printf("eroare creare echipa \n");
            return NULL;
        }

        championship->teams[championship->team_count++] = team_to_add;
    }
    else{
        printf("Campionatul este plin.\n");
    }

    return championship;
}

