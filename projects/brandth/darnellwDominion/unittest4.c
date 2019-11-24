  
/**********************************************************************
 * Haelyn Brandt
 * CS362 Sec 400
 * Assignment 3
 * Testing tribute card function
 * player to left revels then discards the top 2 cards of his deck
 * if revealed card is action card, +2 actions
 *      if treature card, +2 coins
 *      if victory card, +2 cards 
**********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int Assert()
{
    //true
    return 1;
}
int main()
{
    //set your card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    //declare the game state
    struct gameState G;
    int seed = 1000;
    int nextPlayer = 1;

    printf("----- Unit test 4: TRIBUTE CARD -----\n");

    //set the game state
    memset(&G, 23, sizeof(struct gameState));
    //initialize game
    int r = initializeGame(2, k, seed, &G);

    //set variables
    int tributeRevealedCards[2] = {copper, province};

    //check if +2 coins were gained for each treasure card
	printf("TEST 1: test for +2 coins\n");
    //set initial num coins as test 1
    int test1 = G.coins;

    //call refactored tribute function
    int r1 = tribute_function(0, 1, tributeRevealedCards, &G);
    int expcoins = G.coins;
    if (test1 +2 == expcoins)
    {
        Assert();
        printf("Passed: coins increased by 2\n");
    }
    else
    {
        printf("Failed: coins did NOT increase by 2\n");
    }

    //check if +2 cards are gained for each treasure card
	printf("\nTEST 2: test for +2 coins\n");
    //set initial handcount test 2
    int test2 = G.handCount[0];

    //call refactored tribute function
    int r2 = tribute_function(0, 1, tributeRevealedCards, &G);
    int exphandcount = G.handCount[0];

    //check if 2 cards are gained
    if (test2 +2 == exphandcount)
    {
        Assert();
        printf("Passed: 2 new cards gained\n");
    }
    else
    {
        printf("Failed: 2 new cards NOT gained\n");
    }

    //for coverage purposes
    G.deckCount[1] = 1;
    int r3 = tribute_function(0, 1, tributeRevealedCards, &G);
    G.discardCount[1] = 0;
    G.deckCount[1] = 0;
    int r4 = tribute_function(0, 1, tributeRevealedCards, &G);
    G.discardCount[1] = 1;
    int r5 = tribute_function(0, 1, tributeRevealedCards, &G);
    printf("----- FINISHED!! Unit test 4: TRIBUTE CARD -----\n\n");
}