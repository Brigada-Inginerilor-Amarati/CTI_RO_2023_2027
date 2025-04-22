#include "fotbal.h"

int main(void){

    Campionat_t champ = create_championship("La Liga");


    Echipa_t team1 = create_team("Barcelona");
    Echipa_t team2 = create_team("Real Madrid");

    Jucator_t player1 = create_player("Messi", 40);
    Jucator_t player2 = create_player("Ronaldo", 35);
    Jucator_t player3 = create_player("Messi", 100);

    champ = addTeam(champ, team1);
    champ = addTeam(champ, team2);

    team1 = addPlayer(team1, player1, champ);
    team2 = addPlayer(team2, player2, champ);
    team1 = addPlayer(team1, player3, champ);

    printf("\n-----------------\n jucator cautat in echipa \n -------------\n");
    Jucator_t jucator_cautat = searchFootballPlayerInFootbalTeam("Messi", team1);
    if(!jucator_cautat){
        printf("Nu am gasit jucatorul in echipa \n");
    }
    else{
        printf("Am gasit jucatorul cautat, datele lui sunt : \n");
        printPlayer(jucator_cautat);
    }


    printf("\n-----------------\n jucator cautat in campionat \n -------------\n");
    Jucator_t jucator_cautat2 = searchFootballPlayerInFootbalChampionship("Iniesta", champ);
    if(!jucator_cautat2){
        printf("Nu am gasit jucatorul in campionatul dorit\n");
    }
    else{
        printf("Am gasit jucatorul cautat, datele lui sunt : \n");
        printPlayer(jucator_cautat2);
    }

    printf("\n ------------\ndate campionat- echipa-jucatori \n --------------\n");

    printChampionship(champ);

    freeChampionship(champ);
    return 0;
}