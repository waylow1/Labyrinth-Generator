#ifndef LABYRINTH_SCORE_H
#define LABYRINTH_SCORE_H

#include "utils.h"

/**
 * @brief Creates a score file for the specified labyrinth if it does not already exist.
 * 
 * @param labyrinth_name The name of the labyrinth for which to create the score file (without extension).
 * @return int Returns 0 on success, -1 on failure.
 */

int create_score_file_if_not_exists(char * labyrinth_name);


/**
 * @brief Displays the end-of-game dialog and prompts the user for their name and score.
 * 
 * @param score A pointer to the Score structure containing the player's name and score.
 */
void end_of_game_dialog(Score * score);

/**
 * @brief Displays the leaderboard with the list of scores.
 * 
 * @param scores A pointer to an array of Score structures.
 * @param count The number of scores in the array.
 * @return int Returns 0 on success, -1 if there are no scores to display.
 */

int display_ladder(Ladder ladder);

/**
 * @brief Adds a new player's score to the scores array if it qualifies for the leaderboard.
 * 
 * @param ladder A pointer to Ladder structure.
 * @param new_player The Score structure containing the new player's name and score.
 * @return int Returns 0 on success, -1 on failure.
 */

int add_new_score(Ladder * ladder, Score new_player);

/**
 * @brief Sorts the scores in descending order based on the number of coins.
 * @param ladder A pointer to Ladder structure.
 * @param count The number of scores in the array.
 * @return int Returns 0 on success, -1 on failure.
 */
int sort_scores(Ladder * ladder);

/**
 * @brief Loads the scores from a file associated with a specific labyrinth.
 * 
 * @param labyrinth_name The name of the labyrinth associated with the scores (without extension).
 * @param out_count A pointer to store the number of scores loaded.
 * @return void
 */


void  load_labyrinth_scores(Ladder * ladder, const char *labyrinth_name);

/**
 * @brief Dumps the player's score to a file.
 * @param ladder A Ladder structure containing the scores to be dumped.
 * @param count The number of scores to dump.
 * @param labyrinth_name The name of the labyrinth associated with the score (without extension).
 */

int dump_scores(Ladder ladder, char * labyrinth_name);

#endif