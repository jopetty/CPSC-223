//
//  deck.c
//  Deck
//
//  Created by Jackson Petty on 2/20/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "deck.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define DECK_LENGTH	(52) // How long is a standard deck

#define DEC_ALC_ERR	(1) // Return if unable to allocate memory for new deck
#define CRD_ALC_ERR	(2) // Return if unable to allocate memory for new card
#define NDE_ALC_ERR (3) // Return if unable to allocate memory for new node

// MARK:- Data Structures

/**
 Node in the deck.
 
 Should be createed with the `_createNode(Card c)` function.
 When destroyed, only `next` and `previous` are to be `free()`'d.
 
 - Parameters:
 	- next:		Pointer to the next node in the list.
 	- previous:	Pointer to the previous node in the list.
 	- data:		The Card stored in the node.
*/
struct node {
	// TODO: Make it a singly linked list
	struct node * next;
	struct node * previous;
	Card data;
};


/**
 Implementation of a deck of cards as a linked list.
 
 Should be created either with `_deckCreateEmptyDeck()` when an uninitialized
 deck is needed, or with `deckCreate()` to create a full 52 card deck. `deckCreate()`
 is the only public way to create a deck. By default, the deck is ordered first by
 suit, then by rank.
 
 Deck is implemented as a doubly linked list to allow for O(1) insertion at the end
 and for O(1) deletion at the beginning. Being doubly linked also allows for destruction
 in O(n) time, rather than O(n!) time.
 
 - Parameters:
 	- length:	How many cards are in the deck. Should never be set externally.
 	- first:	Pointer to the first node in the deck.
 	- last:		Pointer to the last node in the deck.
*/
struct deck {
	size_t length;
	struct node * first;
	struct node * last;
};

// MARK:- Static Methods

/**
 Creates a new card of a given rank and suit.
 
 Because the struct is passed by value, we do not `malloc()` space for it, and so it never
 needs to be `free()`d.
 
 - Parameters:
 	- rank:	The rank of the card.
 	- suit:	The suit of the card.
 
 - Returns: A new card with given rank and suit.
*/
static inline Card _createCard(char rank, char suit) {
	return (Card) { .rank = rank, .suit = suit };
}

/**
 Creates a new node from a given card.
 
 - Parameter card:	Card to be placed into a node.
 
 - Returns:	A node containing the card, with NULL sequence pointers.
*/
static struct node * _createNode(Card card) {
	
	struct node * n = malloc(sizeof(*n));
	
	if (!n) {
		fprintf(stderr, "Could not allocate memory for a new node.");
		exit(NDE_ALC_ERR);
	}
	
	n->next = NULL;
	n->previous = NULL;
	n->data = card;
	
	return n;
}

/**
 Adds a new node to the end of a deck.
 
 - Parameters:
 	- deck:	Deck to which node will be added.
 	- node:	Node to be placed on the bottom of the deck.
*/
static void _addToEnd(Deck * deck, struct node * node) {
	
	assert(deck);
	assert(node);
		
	node->next = NULL;
	
	if (deck->length++) {
		// Add card to non-empty deck
		node->previous = deck->last;
		deck->last->next = node;
		deck->last = node;
	} else {
		// Deck is empty, we're adding the first card
		node->previous = NULL;
		deck->first = node;
		deck->last = node;
	}
}

/**
 Creates a new, empty deck of length 0.
 
 Function exists as a helper function to ensure that memory was allocated correctly.
 Called from the primary public-facing `createDeck()` and from `deckSplit()`.
 
 - Returns: A pointer to an empty deck.
*/
static Deck * _deckCreateEmptyDeck(void) {
	
	Deck * deck = malloc(sizeof(*deck));
	
	if (!deck) {
		fprintf(stderr, "Could not allocate memory for a new deck.");
		exit(DEC_ALC_ERR);
	}
	
	deck->first = NULL;
	deck->last = NULL;
	deck->length = 0;
	
	return deck;
}

/**
 Attaches part of an old linked list to a new one, and then destroys the old list's
 Deck * wrapper.
 
 - Parameters:
 	- new:	The new deck.
	 - old:	The old deck. The list contained is reassigned, the Deck * struct is `free()`d.
 
 - Complexity:
 Runs in O(1) (constant) time.
*/
static void inline _wireUp(Deck * new, Deck * old) {
	if (new->length) {
		new->last->next = old->first;
		new->last->next->previous = new->last;
		new->last = old->last;
		new->length += old->length;
		free(old);
		old = NULL;
	} else {
		new->first = old->first;
		new->last = old->last;
		new->length = old->length;
		free(old);
		old = NULL;
	}
}

// MARK:- Public Methods

/**
 Creates a new, full deck of 52 cards in order by suit and then rank.
 
 - Returns: A pointer to a full, ordered deck.
 
 - Complexity:
 This runs in O(1) (constant) time, since all decks have the same number of cards
 when initialized.
*/
Deck * deckCreate(void) {
	
	Deck * deck = _deckCreateEmptyDeck();
	
	for (size_t i = 0; i < DECK_LENGTH; i++) {
		
		Card card = _createCard(RANKS[i % strlen(RANKS)],
								SUITS[i / (DECK_LENGTH / strlen(SUITS))]);
		struct node * new_node = _createNode(card);
		
		_addToEnd(deck, new_node);
	}
	
	return deck;
}

/**
 Destoys a deck by `free()`ing all space which was allocated for it.
 
 All nodes which are a part of the deck will be destroyed and set to NULL before
 the deck itself is destroyed and set to NULL. Deck is destroyed from front to back.
 
 - Parameter deck:	Pointer to the deck to be destroyed
 
 - Complexity:
 Runs in O(n) (linear) time, where n is the length of the deck.
*/
void deckDestroy(Deck * deck) {
	
	if (deck) {
		if (deck->length) {
			struct node * tmp = deck->first;
			
			while (deck->length--) {
				if (tmp->next) {
					tmp = tmp->next;
					free(tmp->previous);
					tmp->previous = NULL;
				} else {
					free(tmp);
					tmp = NULL;
				}
			}
		}
	
	free(deck);
	deck = NULL;
	}
}

/**
 Returns whether or not the deck is empty.
 
 - Parameter deck:	A pointer to a deck.
 
 - Returns:	Length of the deck, cast to an integer.
 Since all values not equal to zero are True, the length can be used as a boolean
 to determine if the deck is empty or not.
 
 - Complexity:
 Runs in O(1) (constant) time.
*/
inline int deckNotEmpty(const Deck * deck) {
	return (int)deck->length;
}

/**
 Pops a card off the top of the deck.
 
 - Paramter deck:	A pointer to a deck.
 
 - Retuns: The first card on the top of the deck.
 In the process, the node storing this card is removed from the deck and destroyed,
 and the deck is updated to reflect the new length and first node.
 
 - Complexity:
 Runs in O(1) (constant) time.
*/
Card deckGetCard(Deck * deck) {
	
	assert(deckNotEmpty(deck));
	
	Card card = deck->first->data;
	
	// Prune Deck
	struct node * node = deck->first;
	if (deck->first->next) {
		deck->first = deck->first->next;
	}
	if (deck->first->previous) { // Just set it, dont check?
		deck->first->previous = NULL;
	}
	deck->length--;
	free(node);

	return card;
}

/**
 Places a new card on the bottom of a deck.
 
 Creates a new node wrapper around the card, then places that card into the deck.
 
 - Parameters:
 	- deck:	Deck to which the card is added.
 	- card:	Card added to the deck.
 
 - Complexity:
 Runs in O(1) (constant) time.
*/
inline void deckPutCard(Deck * deck, Card card) {
	struct node * new_node = _createNode(card);
	_addToEnd(deck, new_node);
}

/**
 Splits a deck into two new decks on the nth card in the original deck.
 
 If the original deck contains fewer than n cards, all will be put into first_deck.
 Insted of copying cards into a new deck, we simply wire our new decks up to the
 appropriate parts of the linked list, and then `free()` the Deck * wrapper around
 the old decks.
 
 - Parameters:
 	- deck:			Original deck. Is destroyed after split.
 	- n:			The first n cards are put into first new deck.
 	- first_deck:	Is created from the first n cards of the original deck.
 	- second_deck:	Is created from the remainder of the original deck.
 
 - Complexity:
 If n >= deck->length, then it runs in O(1) (constant) time. Otherwise, it runs in
 O(n) (linear in given n) time.
*/
void deckSplit(Deck * deck, int n, Deck ** first_deck, Deck ** second_deck) {

	Deck * upper_split = _deckCreateEmptyDeck();
	Deck * lower_split = _deckCreateEmptyDeck();
	
	if (n >= deck->length) {
		_wireUp(upper_split, deck);
	} else {
		
		for (size_t i = 0; i < n; i++) {
			deckPutCard(upper_split, deckGetCard(deck));
		}
		_wireUp(lower_split, deck);
	}
	
	*first_deck = upper_split;
	*second_deck = lower_split;
}

/**
 Shuffles two decks together, alternating cards between them.
 
 Both decks passed as parameters will be destroyed, and a new deck containing
 the shuffled cards will be returned to the caller.
 
 - Parameters:
 	- left_deck: A pointer to a deck of cards.
	- right_deck: A pointer to a deck of cards.
 
 - Returns: A pointer to a shuffled deck.
 
 - Complexity:
 Runs in O(n) (linear) time, where n is the length of the shorter deck.
*/
Deck * deckShuffle(Deck * left_deck, Deck * right_deck) {

	Deck * new_deck = _deckCreateEmptyDeck();
	
	size_t iter_length = (left_deck->length < right_deck->length) ? left_deck->length : right_deck->length;
	
	for (size_t i = 0; i < iter_length; i++) {
		deckPutCard(new_deck, deckGetCard(left_deck));
		deckPutCard(new_deck, deckGetCard(right_deck));
	}
	
	if (left_deck->length) {
		deckDestroy(right_deck);
		_wireUp(new_deck, left_deck);
	} else {
		deckDestroy(left_deck);
		_wireUp(new_deck, right_deck);
	}
	
	return new_deck;
}

/**
 Prints out all cards in a deck as a sequence of ranks and suits: AS TC ...
 
 - Parameters:
 	- deck: A pointer to a constant deck.
 	- file: File to which deck will be printed.
 
 -Complexity:
 Runs in O(n) (constant) time, where n is the length of the deck.
*/
void deckPrint(const Deck * deck, FILE * file) {
	struct node * node = deck->first;
	size_t count = deck->length;
	while (node) {
		fprintf(file, "%c%c", node->data.rank, node->data.suit);
		if (--count) { fprintf(file, " "); }
		node = node->next;
	}
}
