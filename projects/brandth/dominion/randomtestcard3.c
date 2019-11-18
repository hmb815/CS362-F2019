/**********************************************************************
 * Haelyn Brandt
 * CS362 Sec 400
 * Assignment 4
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
    // set your card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState G, testG;
    int seed = 1000;

    // set up variables
    int nextPlayer = 0;
    int currentPlayer = 0;
    int numPlayers = 2;
    int count = 0;
    int tributeRevealedCards[2] = {copper, province};
    int treasureIdx = 0;
    int victoryIdx = 0;
    int actionIdx = 0;

    printf("----- Random test Card 3: TRIBUTE CARD -----\n");
    
    // set the game state
    memset(&G, 23, sizeof(struct gameState));
    memset(&testG, 23, sizeof(struct gameState));

    for(int i = 0; i < 1000; i++)
    {
        //random number btwn 2-4 for num of players
        numPlayers = rand() % 3 + 2;
        // initialize game
        int r = initializeGame(numPlayers, k, seed, &G);
        currentPlayer = whoseTurn(&G);
        nextPlayer = (currentPlayer + 1);
        G.deckCount[nextPlayer] = rand() % 2;
        G.discardCount[nextPlayer] = rand() % 2;
        // copy over game state
        memcpy(&testG, &G, sizeof(struct gameState));
        
        // call function
        refac_tribute(&testG, currentPlayer, nextPlayer, tributeRevealedCards);

        //check if tribute card in hand
        for(int j = 0; j < numHandCards(&testG); j++)
        {
            if(testG.hand[currentPlayer][j] == tribute)
            {
                count++;
            }
        }
        
        //next player discard 2 cards
        if(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer] + 2)
        {
            Assert();
        }
        else
        {
            printf("FAILED -- next player did not discard 2 cards\n");
        }

        //loop to see which 2 cards were discarded
        for(int k = 0; k < 2; k++)
        {
            if(tributeRevealedCards[k] == copper || tributeRevealedCards[k] == silver || tributeRevealedCards[k] == gold)
            {
                treasureIdx++;
            }
            else if(tributeRevealedCards[k] == estate || tributeRevealedCards[k] == duchy || tributeRevealedCards[k] == province || tributeRevealedCards[k] == gardens || tributeRevealedCards[k] == great_hall)
            {
                victoryIdx++;
            }
            else
            {
                actionIdx++;
            }
        }

        //test for coins
        if(testG.coins == G.coins + 2)
        {
            Assert();
        }
        else
        {
            printf("FAILED -- coin gained incorrect\n");
        }

        //test for actions
        if(testG.numActions == G.numActions + 2)
        	{
        		Assert();
        	}

        	else
        	{
        		printf("FAILED -- action gained incorrect\n");
        	}

        //test for deck count
        if(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + 2)
        {
            Assert();
        }
		else
        {
			printf("FAILED -- card count incorrect\n");
        }

        
    }
    printf("----- TRIBUTE CARD Random Testing complete -----\n");
}