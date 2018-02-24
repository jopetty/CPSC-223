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

#define DECK_LENGTH (52) // How long is a standard deck
#define ERR_DEC_ALC (1)  // Return if unable to allocate memory for new deck
#define ERR_CRD_ALC (2)  // Return if unable to allocate memory for new card
#define ERR_NDE_ALC (3)  // Return if unable to allocate memory for new node

// MARK:- Data Structures

/**
 Node in the deck.
 
 Should be createed with the @p _createNode(Card c) function.
 When destroyed, only @p next is to be freed, since Cards are
 not dynamically assigned memory.
*/
typedef struct node {
	struct node * next;
	Card data;
} Node;


/**
 Implementation of a deck of cards as a linked list.
 
 Should be created either with @p _deckCreateEmptyDeck() when an uninitialized
 deck is needed, or with @p deckCreate() to create a full 52 card deck. @p deckCreate()
 is the only public way to create a deck. By default, the deck is ordered first by
 suit, then by rank.
 
 Deck is implemented as a singly linked list to allow for O(1) insertion at the end
 and for O(1) deletion at the beginning, as well as linear merging.
*/
struct deck {
	size_t length;
	Node * first;
	Node * last;
};

// MARK:- Static Methods

/**
 Creates a new node from a given card.
 
 @param card	Card to be placed into a node.
 
 @return	A pointer to the node containing the card, with NULL next pointer.
*/
static Node * _createNode(Card card) {
	
	Node * new_node = malloc(sizeof(*new_node));
	
	if (!new_node) {
		fprintf(stderr, "Could not allocate memory for a new node.");
		exit(ERR_NDE_ALC);
	}
	
	new_node->next = NULL;
	new_node->data = card;
	
	return new_node;
}

/**
 Adds a new node to the end of a deck.
 
 @param deck	A pointer to the deck to which node will be added.
 @param	node	A pointer to the node to be placed on the bottom of the deck.
*/
static void _addToEnd(Deck * deck, Node * node) {
	
	assert(deck);
	assert(node);
		
	node->next = NULL;
	(deck->length++) ? (deck->last->next = node) : (deck->first = node);
	deck->last = node;
}

/**
 Creates a new, empty deck of length 0.
 
 Function exists to ensure that memory was allocated correctly.
 Called from the primary public-facing @p createDeck() @p and from @p deckSplit().
 
 @return A pointer to an empty deck.
*/
static Deck * _deckCreateEmptyDeck(void) {
	
	Deck * deck = malloc(sizeof(*deck));
	
	if (!deck) {
		fprintf(stderr, "Could not allocate memory for a new deck.");
		exit(ERR_DEC_ALC);
	}
	
	deck->first = NULL;
	deck->last = NULL;
	deck->length = 0;
	
	return deck;
}

/**
 Attaches part of an old linked list to a new one, and then destroys the old list's
 Deck * wrapper.
 
 @param new	The new deck.
 @param old	The old deck.
 
 @b Complexity:
 Runs in O(1) (constant) time.
*/
static void inline _wireUp(Deck * new, Deck * old) {
	
	(new->length) ? (new->last->next = old->first) : (new->first = old->first);
	new->last = old->last;
	new->length += old->length;
	
	// We don't call deckDestroy() since we only want to delete Deck wrapper, not the nodes
	free(old);
	old = NULL;
}

// MARK:- Public Methods

/**
 Creates a new, full deck of 52 cards in order by suit and then rank.
 
 @return	A pointer to a full, ordered deck.
 
 @b Complexity:
 Runs in O(1) (constant) time, since all decks have the same number of cards
 when initialized.
*/
Deck * deckCreate(void) {
	
	Deck * deck = _deckCreateEmptyDeck();
	
	for (size_t i = 0; i < DECK_LENGTH; i++) {
		Card card = (Card) {
			.rank = RANKS[i % strlen(RANKS)],
			.suit = SUITS[i * strlen(SUITS) / DECK_LENGTH]
		};
		struct node * new_node = _createNode(card);
		_addToEnd(deck, new_node);
	}
	
	return deck;
}

/**
 Destoys a deck by freeing all space which was allocated.
 
 All nodes which are a part of the deck will be destroyed and set to NULL before
 the deck itself is destroyed and set to NULL. Deck is destroyed from front to back.
 
 @param deck	Pointer to the deck to be destroyed.
 
 @b Complexity:
 Runs in O(n) (linear) time, where n is the length of the deck.
*/
void deckDestroy(Deck * deck) {
	
	if (deck) {
		if (deck->length) {
			Node * temp_node;
			Node * curr_node = deck->first;
			while (deck->length--) {
				if (curr_node->next) {
					temp_node = curr_node->next;
					free(curr_node);
					curr_node = temp_node;
				} else {
					free(curr_node);
					curr_node = NULL;
				}
			}
		}
	
	free(deck);
	deck = NULL;
	}
}

/**
 Returns whether or not the deck is empty.
 
 @param deck	A pointer to a deck.
 
 @return	Length of the deck, cast to an integer. Since all values
 not equal to zero are True, the length can be used as a boolean to
 determine if the deck is empty or not.
 
 @b Complexity:
 Runs in O(1) (constant) time.
*/
inline int deckNotEmpty(const Deck * deck) {
	return (int)deck->length;
}

/**
 Pops a card off the top of the deck.
 
 @param deck	A pointer to a deck.
 
 @return	The first card on the top of the deck.
 In the process, the node storing this card is removed from the deck and destroyed,
 and the deck is updated to reflect the new length and first node.
 
 @b Complexity:
 Runs in O(1) (constant) time.
*/
Card deckGetCard(Deck * deck) {
	
	assert(deckNotEmpty(deck));
	
	Card card = deck->first->data;
	
	// Prune Deck
	Node * node = deck->first;
	if (deck->first->next) { deck->first = deck->first->next; }
	deck->length--;
	free(node);
	node = NULL;

	return card;
}

/**
 Places a new card on the bottom of a deck.
 
 Creates a new node wrapper around the card, then places that card into the deck.
 
 @param deck	Deck to which the card is added.
 @param card	Card added to the deck.
 
 @b Complexity:
 Runs in O(1) (constant) time.
*/
inline void deckPutCard(Deck * deck, Card card) {
	Node * new_node = _createNode(card);
	_addToEnd(deck, new_node);
}

/**
 Splits a deck into two new decks on the nth card in the original deck.
 
 If the original deck contains fewer than n cards, all will be put into first_deck.
 Insted of copying cards into a new deck, we simply wire our new decks up to the
 appropriate parts of the linked list, and then free the  wrapper around the old decks.
 
 @param deck		Original deck. Is destroyed after split.
 @param n			Number of cards put into first deck.
 @param first_deck	Created from the first n cards of the original deck.
 @param second_deck	Created from the remainder of the original deck.
 
 @b Complexity:
 If n >= deck length, then it runs in O(1) (constant) time. Otherwise, it runs in
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
 
 @param left_deck	A pointer to a deck of cards.
 @param right_deck	A pointer to a deck of cards.
 
 @return	A pointer to a shuffled deck.
 
 @b Complexity:
 Runs in O(n) (linear) time, where n is the length of the shorter deck.
*/
Deck * deckShuffle(Deck * left_deck, Deck * right_deck) {
	
	Deck * new_deck = _deckCreateEmptyDeck();
	size_t iter_length = (left_deck->length < right_deck->length) ? left_deck->length : right_deck->length;
	
	for (size_t i = 0; i < iter_length; i++) {
		deckPutCard(new_deck, deckGetCard(left_deck));
		deckPutCard(new_deck, deckGetCard(right_deck));
	}
	
	// Wire any remaining cards up to the new deck
	if (left_deck->length > right_deck->length) {
		deckDestroy(right_deck);
		_wireUp(new_deck, left_deck);
	} else if (right_deck->length > left_deck->length) {
		deckDestroy(left_deck);
		_wireUp(new_deck, right_deck);
	} else {
		deckDestroy(left_deck);
		deckDestroy(right_deck);
	}
	
	return new_deck;
}

/**
 Prints out all cards in a deck as a sequence of ranks and suits: AS TC ...
 
 @param deck	A pointer to a constant deck.
 @param file	File to which deck will be printed.
 
 @b Complexity:
 Runs in O(n) (linear) time, where n is the length of the deck.
*/
void deckPrint(const Deck * deck, FILE * file) {
	
	Node * curr_node = deck->first;
	size_t count = deck->length;
	
	while (curr_node) {
		fprintf(file, "%c%c", curr_node->data.rank, curr_node->data.suit);
		if (--count) { fprintf(file, " "); }
		curr_node = curr_node->next;
	}
}
