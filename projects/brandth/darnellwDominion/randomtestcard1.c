/**********************************************************************
 * Haelyn Brandt
 * CS362 Sec 400
 * Assignment 4
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
    // set your card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState G, testG;
    int seed = 1000;

    // set up variables
    int choice1 = 0;
    int currentPlayer = 0;
    int numPlayers;
    int count = 0;
    int trash = 0;

    printf("----- Random test Card 1: BARON CARD -----\n");
    
    // set the game state
    memset(&G, 23, sizeof(struct gameState));
    memset(&testG, 23, sizeof(struct gameState));

    for(int i = 0; i < 1000; i++)
    {
        //random number btwn 2-4 for num of players
        numPlayers = rand() % 3 + 2;
        //two choices 0 or 1 (estate or no estate)
        choice1 = rand() % 2;

        // initialize game
        int r = initializeGame(numPlayers, k, seed, &G);
        currentPlayer = whoseTurn(&G);
        G.numBuys = rand() % 30;

        // randomize variable set
        if (rand() % 10 == 3)
        {
            G.handCount[currentPlayer] = -1;
        }

        // copy over game state
        memcpy(&testG, &G, sizeof(struct gameState));
        
        // call baron function
        baron_function(currentPlayer, &testG, choice1);

        //loop through hand to find num of estate cards
        for(int j = 0; j < numHandCards(&G); j++)
        {
            if(G.hand[currentPlayer][j] == estate)
            {
                count++;
            }
        }

        // Test for numBuys
        if(testG.numBuys == G.numBuys + 1)
        {
            Assert();
        }
        else
        {
            printf("FAILED -- numBuys incorrect\n");
        }

        // Test for deck count
        if(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer])
        {
            Assert();
        }
		else
        {
			printf("FAILED -- deck count incorrect\n");
        }

        // Test for choice1 == 0
        if (choice1 == 0){
            if (supplyCount(estate, &G) > 0)
            {
                if(testG.supplyCount[estate] < G.supplyCount[estate])
                {
                    Assert();
                }
                else
                {
                    printf("FAILED -- estate gained but supply count incorrect\n");
                }
            }
        }

        //if player has estate
        if(count >= 1)
        {
            //test will fail because I introduced a bug to change gained coins to 3 instead of 4
            if(testG.coins == G.coins + 4)
            {
                Assert();
            }
            else
            {
                printf("FAILED -- did not gain 4 coins when player had estate card in hand\n");
            }
        }

        //test discard baron card
        for(int k = 0; k < numHandCards(&testG); k++)
        {
            if(testG.hand[currentPlayer][k] == baron)
            {
                trash = 1;
            }
        }

        if(trash == 0)
        {
            Assert();
        }
        else
        {
            printf("FAILED -- did not trash baron card\n");
        }

    }

    printf("----- BARON CARD Random Testing complete -----\n");
}