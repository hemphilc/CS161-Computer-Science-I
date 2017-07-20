/**
  * @brief Assignment 9
  * @author Corey Hemphill
  */

#ifndef QBFUNCTIONS
#define QBFUNCTIONS

//Constants//
const int NUM_GAMES = 10;
const int NUM_STATS = 5;

//Stats//
enum stats {COMPLETIONS, ATTEMPTS, YARDS, TOUCHDOWNS, INTERCEPTIONS};

//Struct//
struct Quarterback {
    string nameFirst;
    string nameLast;
    int gameLog[NUM_GAMES][NUM_STATS];
};

//Functions//
/**
 * @brief readQbs Reads in quarterback data for a specified number of quarterbacks from a file
 * @param fileName "QBInfo.txt" Quarterback data text file name
 * @param numRecords Returns the number of quarterback records read in by reference
 * @return
 */
Quarterback* readQbs(const string fileName, int& numRecords);

/**
 * @brief getQbMenu Prompts Quarterback Menu
 * @param qbList Pointer to Quarterback struct array
 * @param numRecords Number of records
 */
void getQbMenu(Quarterback* qbList, int numRecords);

/**
 * @brief printPlayer Prints out player name and stats for all ten games
 * @param qbList Pointer to Quarterback struct array
 * @param player Player at list number
 */
void printPlayer(Quarterback* qbList, int player);

/**
 * @brief printPlayerStats Prints out respective total of each stat for a given player
 * @param qbList Pointer to Quarterback struct array
 * @param player Player at list number
 */
void printPlayerStats(Quarterback* qbList, int player);

/**
 * @brief getStatTotal Finds the totals for each respective stat in the stats array for a given quarterback
 * @param qbList Pointer to Quarterback struct array
 * @param comps Reference to total completions
 * @param atts Reference to total attempts
 * @param yards Reference to total yards
 * @param tds Reference to total touchdowns
 * @param ints Reference to total ints
 * @param player Player at list number
 */
void getStatTotal(Quarterback* qbList, int& comps, int& atts, int& yards, int& tds, int& ints, int player);

/**
 * @brief printPasserRatings Calculates and prints out passer rating for the given stats
 * @param qbList Pointer to Quarterback struct array
 * @param numRecords Number of records
 */
void printPasserRatings(Quarterback* qbList, int numRecords);

/**
 * @brief checkValueLimit Checks incoming value is within the specified domain (0, 2.375). If x > 2.375, x = 2.375. If x < 0, x = 0.
 * @param x Passer rating value (a, b, c, or d)
 */
void checkValueLimit(double& x);


#endif // QBFUNCTIONS

