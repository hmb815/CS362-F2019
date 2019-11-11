//unit test 1 is testing the baron function
//+1 buy
//discard Estate for +4 
//OR gain an Estate


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
    struct gameState state, testState;
    int k[10] = {adventurer, minion, feast, gardens, mine,
                    ambassador, smithy, village, baron, tribute};

    printf("Begin Testing Baron Card\n");
    //set game state
    r = initializeGame(numPlayers, k, seed, &state);
    if (r == -1)
        printf("ERROR - Game initialization failed.\n"); 
    memcpy(&testState, &state, sizeof(struct gameState));

    //give Baron card to player
    testState.hand[currPlayer][testState.handCount[currPlayer]] = baron;
    testState.handCount[currPlayer]++;
    if (state.handCount[currPlayer] + 1 == testState.handCount[currPlayer])
        printf("PASSED - Baron card given to player.\n");
    else
        printf("ERROR - Baron card not given.\n");

    //call refactored function
    refac_baron(&testState, 0, currPlayer);

    //check for +1 buy
    if (state.numBuys + 1 == testState.numBuys)
        printf("PASSED - Player 1 gained +1 buy.\n");
    else
        printf("ERROR - Player 1 did not get +1 buy.\n");

    
    //Check if estate was discarded and coins gained
	if(state.discardCount(estate[i]) == testState.discardCount(estate[i]))
        if(state.coins + 4 == testState.coins)
		    printf("PASSED - estate card was discarded and 4 coins gained\n");	
	    else
		    printf("ERROR - estate card was not discarded and no coins gained.\n");


    //Check if card was discarded
	if(state.discardCount[currPlayer] == testState.discardCount[currPlayer])
		printf("PASSED - Baron card was discarded\n");	
	else
		printf("ERROR - Baron card was not discarded.\n");

    printf("Baron Card Test Complete\n\n");

    return 0;
   
}