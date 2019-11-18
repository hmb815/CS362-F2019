/**********************************************************************
 * Haelyn Brandt
 * CS362 Sec 400
 * Assignment 4
 * Testing minion card function
 * +1 action
 * choose 1: +2 coins
 * OR discard hand, +4 cards, and each other player with at least 5 cards in hand
 *      discard their hand and draws 4 cards
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
    int choice2 = 0;
    int handPos = 0;
    int currentPlayer = 0;
    int numPlayers = 2;
    int count = 0;

    printf("----- Random test Card 2: MINION CARD -----\n");
    
    // set the game state
    memset(&G, 23, sizeof(struct gameState));
    memset(&testG, 23, sizeof(struct gameState));

    for(int i = 0; i < 1000; i++)
    {
        //random number btwn 2-4 for num of players
        numPlayers = rand() % 3 + 2;
        //two choices 0 or 1
        choice1 = rand() % 2;
        choice2 = rand() % 2;

        // initialize game
        int r = initializeGame(numPlayers, k, seed, &G);
        currentPlayer = whoseTurn(&G);
        G.numActions = rand() % 30;

        // randomize variable set
        if (rand() % 10 == 3)
        {
            G.handCount[currentPlayer] = -1;
        }

        // copy over game state
        memcpy(&testG, &G, sizeof(struct gameState));
        
        // call minion function
        refac_minion(&testG, handPos, currentPlayer, choice1, choice2);

        //check if minion card in hand
        for(int j = 0; j < numHandCards(&testG); j++)
        {
            if(testG.hand[currentPlayer][j] == minion)
            {
                count++;
            }
        }

        // Test for numActions
        if(testG.numActions - 1 == G.numActions)
        {
            Assert();
        }
        else
        {
            printf("FAILED -- numActions incorrect\n");
        }

        // Test for gaining 2 coins
        if (choice1)
        {
            if (testG.coins == G.coins + 2)
            {
                Assert();
            }
            else
            {
                printf("FAILED -- coin count incorrect\n");
            }
        }

        // Test for deck count
        if (testG.discardCount[currentPlayer] == G.discardCount[currentPlayer] + 1)
        {
            Assert();
        }
		else
        {
			printf("FAILED -- discard count incorrect\n");
        }

        
    }
    printf("----- MINION CARD Random Testing complete -----\n");
}