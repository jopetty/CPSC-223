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
	
//	// Implement example.in
//	//
//	// Create a new deck and print it
//	Deck * deck = deckCreate();
//	printf("Initial Deck:\n"); deckPrint(deck, stdout); printf("\n\n");
//	// Remove a card from the top of the deck
//	Card top_card = deckGetCard(deck);
//	// Put it back on the bottom
//	deckPutCard(deck, top_card);
//	// Split the deck into two decks
//	Deck * f_deck;
//	Deck * s_deck;
//	deckSplit(deck, 17, &f_deck, &s_deck);
//	printf("New f_deck:\n"); deckPrint(f_deck, stdout); printf("\n\n");
//	printf("New s_deck:\n"); deckPrint(s_deck, stdout); printf("\n\n");
//	// Shuffle the decks together
//	deck = deckShuffle(f_deck, s_deck);
//	printf("Shuffled Deck:\n"); deckPrint(deck, stdout); printf("\n\n");
//	// Split into a non-empty and an empty deck
//	Deck * n_deck;
//	Deck * d_deck;
//	deckSplit(deck, 100000, &n_deck, &d_deck);
//	printf("New n_deck length: %d\n", deckNotEmpty(n_deck));
//	printf("New n_deck:\n"); deckPrint(n_deck, stdout); printf("\n\n");
//	printf("New d_deck length: %d\n", deckNotEmpty(d_deck));
//	printf("New d_deck:\n"); deckPrint(d_deck, stdout); printf("\n\n");
//
//	deckDestroy(n_deck);
//	deckDestroy(d_deck);
	
//	// Implement bigDeck.in (small version)
//	Deck * c1 = deckCreate();
//	Deck * c2 = deckCreate();
//
//	Deck * d3 = deckShuffle(c1, c2);
//
//	deckPrint(d3, stdout);
//
//	deckDestroy(d3);
	
	// Test splitting with unitizialized target decks
	Deck * d1 = NULL;
	Deck * d2 = NULL;
	Deck * og_deck = deckCreate();
	
	printf("OG Deck:\n");
	deckPrint(og_deck, stdout);
	printf("\n\n");
	
	deckSplit(og_deck, 10, &d1, &d2);
	
	printf("Deck 1:\n");
	deckPrint(d1, stdout);
	printf("\n\n");
	
	printf("Deck 2\n");
	deckPrint(d2, stdout);
	printf("\n\n");
	
	deckDestroy(d1);
	deckDestroy(d2);
	
	// Split to the same deck
	Deck * d3 = deckCreate();
	Deck * d4 = NULL;
	
	deckSplit(d3, 10, &d4, &d4);
	
	printf("Deck 4:\n");
	deckPrint(d4, stdout);
	printf("\n\n");
	
	deckDestroy(d4);
	
	// Split a deck to itself
	Deck * selfdeck = deckCreate();
	
	deckSplit(selfdeck, 10, &selfdeck, &selfdeck);
	
	printf("Deck 5:\n");
	deckPrint(selfdeck, stdout);
	printf("\n\n");
	
//	Deck * shuffdeck = deckShuffle(selfdeck, selfdeck);
//
//	printf("Deck 6:\n");
//	deckPrint(shuffdeck, stdout);
//	printf("\n\n");
//
//	deckDestroy(shuffdeck);
	
	// Empty shuffle
//	Deck * regdeck = deckCreate();
	Deck * emptdeck = NULL;
	
	Deck * outdeck = deckShuffle(emptdeck, emptdeck);
	
	printf("Deck 1:\n");
	deckPrint(outdeck, stdout);
	printf("\n\n");
	
	// Plit empty decks
	Deck * ndeck = NULL;
	Deck * regdeck = deckCreate();
	for (int i = 0; i < 52; i++) {
		deckGetCard(regdeck);
	}
	
	Deck * out1 = NULL;
	Deck * out2 = NULL;
	
	deckSplit(regdeck, 10, &out1, &out2);
	
	printf("OG Deck:\n");
	deckPrint(out1, stdout);
	printf("\n\n");
	
	printf("OG Deck:\n");
	deckPrint(out2, stdout);
	printf("\n\n");

	return 0;
}
