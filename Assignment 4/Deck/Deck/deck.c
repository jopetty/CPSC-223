//
//  deck.c
//  Deck
//
//  Created by Jackson Petty on 2/20/18.
//  Copyright © 2018 Jackson Petty. All rights reserved.
//

#include "deck.h"
#include <stdlib.h>

#define DECK_LENGTH	(52)
#define SUITS_LENGTH	(4)
#define RANKS_LENGTH	(13)

#define DEC_ALC_ERR	(1)
#define CRD_ALC_ERR	(2)

// MARK: Data Structures
struct card {
	char rank;
	char suit;
};

struct deck {
	uint8_t length;
	Card * cards[DECK_LENGTH];
};

Deck * deckCreate(void) {
	
	Deck * d = malloc(sizeof(*d));
	
	if (!d) {
		fprintf(stderr, "Could not allocate memory for a new deck.");
		exit(DEC_ALC_ERR);
	}
	
	d->length = DECK_LENGTH;
	for (size_t i = 0; i < DECK_LENGTH; i++) {
		Card * new_card = malloc(sizeof(*new_card));
		if (!new_card) {
			fprintf(stderr, "Could not allocate memory for a new card.");
			exit(CRD_ALC_ERR);
		}
		new_card->rank = RANKS[];
		new_card->suit = SUITS[];
		d->cards[i] = new_card;
	}
	
	return d;
}

void deckDestroy(Deck * d) {
	if (d) {
		for (size_t i = 0; i < d->length; i++) {
			if (d->cards[i]) {
				free(d->cards[i]);
				d->cards[i] = NULL;
			}
		}
		free(d);
		d = NULL;
	}
}

int deckNotEmpty(const Deck * d) {
	return d->length;
}
