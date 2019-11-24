/**********************************************************************
 * Haelyn Brandt
 * CS362 Sec 400
 * Assignment 3
 * Testing baron card function
 * +1 buy
 * discard Estate for +4 OR gain an Estate
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

    printf("----- Unit test 1: BARON CARD -----\n");

    //set the game state
    memset(&G, 23, sizeof(struct gameState));
    //initialize game
    int r = initializeGame(2, k, seed, &G);

    //check if the number of buys were increased
	printf("TEST 1: test for +1 buy\n");

    //set initial num buys as test 1
    int test1 = G.numBuys;
    
    //call refactored baron function
    int r1 = baron_function(0, &G, 0);
    int expnumbuy = G.numBuys;

    //check if numBuys +1 after calling baron_function
    if (test1 +1 == expnumbuy)
    {
        Assert();
        printf("Passed: num buy increased\n");
    }
    else
    {
        printf("Failed: num buy did NOT increase\n");
    }

    //check if +4 coins were gained after discarding estate
	printf("\nTEST 2: test for +4 coins\n");
    //set initial num coins as test 2
    int test2 = G.coins;

    //call refactored baron function
    //set choice to 1
    int r2 = baron_function(0, &G, 1);
    int expcoins = G.coins;

    //check if coins +4 after calling refac_baron
    if(test2 +4 == expcoins)
    {
        Assert();
        printf("Passed: coins increased by 4\n");
    }
    else
    {
        printf("Failed: coins did NOT increase by 4\n");
    }

    //check if handcount decreased after discarding estate
    printf("\nTest 3: discarding estate decreases handcount\n");
    //set initial handcount as test 3
    int test3 = G.handCount[0];

    //call refactored baron function
    //set choice to 1
    int r3 = baron_function(0, &G, 1);
    int exphandcount = G.handCount[0];

    //check if handcount -1 = expected handcount
    if(test3 -1 == exphandcount)
    {
        Assert();
        printf("Passed: handcard decreased \n");
    }
    else
    {
        printf("Failed: handcount did NOT decrease\n");
    }

    //for coverage purposes
    G.supplyCount[estate] = 2;
    G.handCount[0] = -1;

    //call refactored baron function
    int r4 = baron_function(0, &G, 1);
    printf("----- FINISHED!! Unit test 1: BARON CARD -----\n\n");
}