/**********************************************************************
 * Haelyn Brandt
 * CS362 Sec 400
 * Assignment 3
 * Testing minion card function
 * +1 action
 * choose 1: +2 coins
 * OR discard hand, +4 cards, and each other player with at least 5 cards in hand
 *      discard their hand and draws 4 cards
 * Fixed for assignment 5
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

    printf("----- Unit test 2: MINION CARD -----\n");
    //set the game state
    memset(&G, 23, sizeof(struct gameState));
    //initialize game
    int r = initializeGame(2, k, seed, &G);
    

    //check if action + 1
	printf("TEST 1: test for +1 action\n");
    //set initial num actions as test 1
    int test1 = G.numActions;

    //call refactored minion function (choice 1)
    int r1 = minion_function(1, 0, 0, &G, 0, 0);
    int expnumact = G.numActions;

    //check if numactions+1 after calling minion_function
    if (test1 +1 == expnumact)
    {
        Assert();
        printf("Passed: num actions increased\n");
    }
    else
    {
        printf("Failed: num actions did NOT increase\n");
    }


    //check if +2 coins were gained (choice 1)
	printf("\nTEST 2: test for +2 coins\n");
    //set initial num coins as test 2
    int test2 = G.coins;

    //call refactored minion function
    int r2 = minion_function(0, 0, 0, &G, 0, 0);
    int expcoins = G.coins;

    //check if +2 coins were gained
    if (test2 +2 == expcoins)
    {
        Assert();
        printf("Passed: coins increased by 2\n");
    }
    else
    {
        printf("Failed: coins did NOT increase by 2\n");
    }


    //check if player gained 4 cards (choice 2)
	printf("\nTEST 3: player gained 4 cards\n");
    //set initial handcount as test 3
    int test3 = G.handCount[0];

    //call refactored minion function
    //set choice 2 to 1
    int r3 = minion_function(0, 1, 0, &G, 0, 0);
    int exphandcount = G.handCount[0];

    //check if player drew 4 cards
    if (test3 +4 == exphandcount)
    {
        Assert();
        printf("Passed: player drew 4 cars\n");
    }
    else
    {
        printf("Failed: player did NOT draw 4 cards\n");
    }
    
    //for executing and coverage purposes
    G.handCount[1] = 5;

    //call refactored minion function
    //set choice 1 to 1
    int r4 = minion_function(1, 0, 0, &G, 0, 0);
    printf("----- FINISHED!! Unit test 2: MINION CARD -----\n\n");
}