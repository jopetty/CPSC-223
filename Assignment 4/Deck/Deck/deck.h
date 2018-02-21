//
//  deck.h
//  Deck
//
//  Created by Jackson Petty on 2/20/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#ifndef deck_h
#define deck_h

#include <stdio.h>

// Standard suits and ranks
#define SUITS "CDHS"
#define RANKS "A23456789TJQK"

// A single card
// This is small enough that we usually pass it
// around by copying instead of using pointers.
typedef struct card {
	char rank;   /* from RANKS */
	char suit;   /* from SUITS */
} Card;

// A deck of cards
typedef struct deck Deck;

// Create a new unshuffled deck of 52 cards,
// ordered by suit then rank:
//
// AC 2C 3C ... KC AD 2D 3D ... KD AH 2H 3H ... KS
Deck *deckCreate(void);

// Free all space used by d.
// Running time should be O(length of deck)
void deckDestroy(Deck *d);

// Return true if deck is not empty.
// Running time should be O(1).
int deckNotEmpty(const Deck *d);

// Remove and return the top card of a deck.
// If deck is empty, behavior is undefined.
// Running time should be O(1).
Card deckGetCard(Deck *d);

// Add a card to the bottom of a deck.
// This is not required to do anything special if the card is bogus
//   (e.g. "1C", "?X", "A-").
// Running time should be O(1).
void deckPutCard(Deck *d, Card c);

// Split a deck into two piles:
//    *d1 is new deck with first n cards in d.
//    *d2 is new deck with remaining cards in d.
// Order of cards is preserved.
// If d contains fewer than n cards, put them all in d1.
// Destroys d.
// Running time should be O(n).
void deckSplit(Deck *d, int n, Deck **d1, Deck **d2);

// Shuffle two decks together by alternating cards from
// d1 and d2 to obtain new deck.
//
// If d1 is X X X X
// and d2 is Y Y Y Y Y Y Y,
// return value is X Y X Y X Y X Y Y Y Y.
//
// If d1 is X X X X
// and D2 is Y Y,
// return value is X Y X Y X X.
//
// Running time should be O(length of shorter deck).
// Destroys d1 and d2.
Deck *deckShuffle(Deck *d1, Deck *d2);

// Print the contents of deck to f as sequence of ranks/suits
// separated by spaces.
// Example output: "AS TC 9D 3H 5S" (without quotes)
// Running time should be O(length of deck).
void deckPrint(const Deck *d, FILE *f);

#endif /* deck_h */
