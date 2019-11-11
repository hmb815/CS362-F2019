//unit test 2 is testing the minion function
//+1 action
//choose 1: +2 coins
//OR discard hand, +4 cards, and each other player with at least 5 cards in hand
//  discard their hand and draws 4 cards


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

    printf("Begin Testing Minion Card\n");
    //set game state
    r = initializeGame(numPlayers, k, seed, &state);
    if (r == -1)
        printf("ERROR - Game initialization failed.\n"); 
    memcpy(&testState, &state, sizeof(struct gameState));

    //give Minion card to player
    testState.hand[currPlayer][testState.handCount[currPlayer]] = minion;
    testState.handCount[currPlayer]++;
    if (state.handCount[currPlayer] + 1 == testState.handCount[currPlayer])
        printf("PASSED - Minion card given to player.\n");
    else
        printf("ERROR - Minion card not given.\n");

    //call refactored function
    refac_minion(&testState, 0, currPlayer, 0, 0);


    //Check for +1 Action
	if(state.numActions + 1 == testState.numActions)
		printf("Passed where two extra actions were added\n");
	else
		printf("Failed where two extra actions were not added\n");

    //check if other players discarded hand and redrawn if hand size > 4
    for(i = 0; i < state.numPlayers; i++){
        if( i != currPlayer){
            if(state.handCount[i] > 4)
                if(state.discardCount[i] == testState.discardCount[i])
		            printf("PASSED - card were discarded\n");	
	            else
		            printf("ERROR - card were not discarded.\n");
            if (state.handCount[i] + 4 == testState.handCount[i])
                printf("SUCCESS - Players drew 4 new cards\n");
            else
                printf("ERROR - Players did not draw correct # of cards.\n")
        }
    }


    //Check if card was discarded
	if(state.discardCount[currPlayer] == testState.discardCount[currPlayer])
		printf("PASSED - Minion card was discarded\n");	
	else
		printf("ERROR - Minion card was not discarded.\n");

    printf("Minion Card Test Complete\n\n");

    return 0;
   
}