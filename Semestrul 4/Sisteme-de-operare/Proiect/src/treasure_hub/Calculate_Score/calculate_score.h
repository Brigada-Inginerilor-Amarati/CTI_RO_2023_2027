#ifndef __CALCULATE_SCORE
#define __CALCULATE_SCORE

// -----------------
// Includes
// -----------------

#include "../../treasure_manager/treasure_manager.h"

// -----------------
// Structs
// -----------------

typedef struct Nod_Score{
    char userName[MAX_ID_LEN];
    int totalScore;
    struct Nod_Score *next_node;
}Nod_Score_T;

typedef struct Nod_Score *List_Score_T;

// -----------------
// Functions
// -----------------

List_Score_T create_list();

List_Score_T get_or_create_node(List_Score_T list, const char *userName);

int calculate_score(const char *hunt_id, const char *userName);

List_Score_T calculate_all_scores(const char *hunt_id);

void print_scores(List_Score_T list);

void free_score_list(List_Score_T list);

#endif