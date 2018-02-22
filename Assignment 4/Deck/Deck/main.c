//
//  main.c
//  Deck
//
//  Created by Jackson Petty on 2/20/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "deck.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
	
	// Implement example.in
	//
	// Create a new deck and print it
	Deck * deck = deckCreate();
	printf("Initial Deck:\n"); deckPrint(deck, stdout); printf("\n\n");
	// Remove a card from the top of the deck
	Card top_card = deckGetCard(deck);
	// Put it back on the bottom
	deckPutCard(deck, top_card);
	// Split the deck into two decks
	Deck * f_deck;
	Deck * s_deck;
	deckSplit(deck, 17, &f_deck, &s_deck);
	printf("New f_deck:\n"); deckPrint(f_deck, stdout); printf("\n\n");
	printf("New s_deck:\n"); deckPrint(s_deck, stdout); printf("\n\n");
	// Shuffle the decks together
	deck = deckShuffle(f_deck, s_deck);
	printf("Shuffled Deck:\n"); deckPrint(deck, stdout); printf("\n\n");
	// Split into a non-empty and an empty deck
	Deck * n_deck;
	Deck * d_deck;
	deckSplit(deck, 100000, &n_deck, &d_deck);
	printf("New n_deck length: %d\n", deckNotEmpty(n_deck));
	printf("New n_deck:\n"); deckPrint(n_deck, stdout); printf("\n\n");
	printf("New d_deck length: %d\n", deckNotEmpty(d_deck));
	printf("New d_deck:\n"); deckPrint(d_deck, stdout); printf("\n\n");
	
	deckDestroy(n_deck);
	deckDestroy(d_deck);

	return 0;
}
