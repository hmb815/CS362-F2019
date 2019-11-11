//unit test 4 is testing the tribute function
//player to left revels then discards the top 2 cards of his deck
//if revealed card is action card, +2 actions
//  if treature card, +2 coins
//  if victory card, +2 cards


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

    printf("Begin Testing Tribute Card\n");
    //set game state
    r = initializeGame(numPlayers, k, seed, &state);
    if (r == -1)
        printf("ERROR - Game initialization failed.\n"); 
    memcpy(&testState, &state, sizeof(struct gameState));

    //give Tribute card to player
    testState.hand[currPlayer][testState.handCount[currPlayer]] = tribute;
    testState.handCount[currPlayer]++;
    if (state.handCount[currPlayer] + 1 == testState.handCount[currPlayer])
        printf("PASSED - Tribute card given to player.\n");
    else
        printf("ERROR - Tribute card not given.\n");

    //call refactored function
    refac_tribute(&testState, currPlayer);

    //check and see if two coins were added for treasure cards
    for (i = 0; i < state.tributeRevealedCards[0]; i++)
    {
        if(state.tributeRevealedCards[0][i]) == copper || state.tributeRevealedCards[0][i]) == silver || state.tributeRevealedCards[0][i]) == gold)
            if(state.coins + 2 == teststate.coins)
                printf("PASSED - two extra coins were added\n");
	        else
		        printf("ERROR - two extra coins were not added\n");

        else if (state.tributeRevealedCards[0][i]) == estate || state.tributeRevealedCards[0][i]) == duchy || state.tributeRevealedCards[0][i]) == province || state.tributeRevealedCards[0][i]) == gardens || state.tributeRevealedCards[0][i]) == great_hall)
            if (state.handCount[currPlayer] + 2 == testState.handCount[currPlayer])
                    printf("SUCCESS - Player drew 2 new cards\n");
            else
                    printf("ERROR - Player did not draw 2 cards.\n");

        else
            if(state.numActions + 2 == testState.numActions)
		        printf("Passed where two extra actions were added\n");
	        else
		        printf("Failed where two extra actions were not added\n");
    }


    printf("Tribute Card Test Complete\n\n");

    return 0;
   
}