//unit test 3 is testing the ambassador function
//reveal a card from hand, return up to 2 copies of it from hand to supply
//each other player gains a copy of it

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

    printf("Begin Testing Ambassador Card\n");
    //set game state
    r = initializeGame(numPlayers, k, seed, &state);
    if (r == -1)
        printf("ERROR - Game initialization failed.\n"); 
    memcpy(&testState, &state, sizeof(struct gameState));

    //give Ambassador card to player
    testState.hand[currPlayer][testState.handCount[currPlayer]] = ambassador;
    testState.handCount[currPlayer]++;
    if (state.handCount[currPlayer] + 1 == testState.handCount[currPlayer])
        printf("PASSED - Ambassador card given to player.\n");
    else
        printf("ERROR - Ambassador card not given.\n");

    //call refactored function
    refac_ambassador(&testState, 0, 0, 0, currPlayer);


    //Check if card was discarded
	if(state.discardCount[currPlayer] == testState.discardCount[currPlayer])
		printf("PASSED - Ambassador card was discarded\n");	
	else
		printf("ERROR - Ambassador card was not discarded.\n");

    printf("Ambassador Card Test Complete\n\n");

    return 0;
   
}