//unit test 5 is testing the mine function
//may trash a treasure from your hand.
//Gain a treasure to your hand costing up to 3 more than it



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() 
{
    int i;
    int r;
    int seed = 1000;
    int numPlayers = 4;
    int currPlayer = 0;
    int handCount = 0;
    int deckCount = 0;
    int discardCount = 0;
    struct gameState state, testState;
    int treasure[3] = {copper, silver, gold};
    int k[10] = {adventurer, minion, feast, gardens, mine,
                    ambassador, smithy, village, baron, tribute};

    printf("Begin Testing Mine Card\n");
    //set game state
    r = initializeGame(numPlayers, k, seed, &state);
    if (r == -1)
        printf("ERROR - Game initialization failed.\n"); 
    memcpy(&testState, &state, sizeof(struct gameState));

    //give Mine card to player
    testState.hand[currPlayer][testState.handCount[currPlayer]] = mine;
    testState.handCount[currPlayer]++;
    if (state.handCount[currPlayer] + 1 == testState.handCount[currPlayer])
        printf("PASSED - Mine card given to player.\n");
    else
        printf("ERROR - Mine card not given.\n");

    //call refactored function
    refac_mine(&testState, currPlayer, 0, 0, 0);

    handCount = state.handCount[currPlayer];
    deckCount = state.deckCount[currPlayer];
    discardCount = state.discardCount[currPlayer];
    
    //check if treasure +3 was gained
    if((getCost(state.handCount[currPlayer](treasure[i])) + 3) == (getCost(testState.handCount[currPlayer](treasure[i]))))
        printf("SUCCESS - Player revealed treasure and gained +3\n");
    else
        printf("ERROR - Player revealed treasure and did not gain +3\n");


    //Check if treasure was discarded
	if(state.discardCount(treasure[i]) == testState.discardCount(treasure[i]))
		printf("PASSED - treasure card was discarded\n");	
	else
		printf("ERROR - treasure card was not discarded.\n");


    //Check if card was discarded
	if(state.discardCount[currPlayer] == testState.discardCount[currPlayer])
		printf("PASSED - Mine card was discarded\n");	
	else
		printf("ERROR - Mine card was not discarded.\n");


    printf("Mine Card Test Complete\n\n");

    return 0;
   
}