//#include <stdio.h>
//#include <stdlib.h>
//#include <assert.h>
//#include <ctype.h>
//
//#include "deck.h"
//
//// Deck tester
////
//// Implements Deck Assembly Language.
////
//// We have registers 0..N-1.
////
//// Each command is taken from stdin using scanf.
////
//// c d       - create new deck, put in register d
//// d d       - destroy deck in register d
//// e d       - print 1 if deck d is not empty, 0 otherwise
//// - d       - get and print top card in deck d, followed by newline
//// + d c     - put card to deck d
//// / d1 d2 n - split deck in d1 to d1 and d2
//// * d1 d2   - shuffle d1 and d2, output to d1
//// p d       - print deck d, followed by newline
//// q         - exit
//// # comment - ignore all text to end of line
//
//#define N (1024)  // number of deck registers
//
//#define Error(x) (fprintf(stderr, "%s: " x "\n", argv[0]), exit(1))
//
//int
//main(int argc, char **argv)
//{
//    if(argc != 1) {
//        fprintf(stderr, "Usage: %s\n", argv[0]);
//        return 1;
//    }
//
//    Deck *d[N];
//    char command;
//    int d1;
//    int d2;
//    int n;
//    Card c;
//
//    while((command = getchar()) != EOF) {
//        switch(command) {
//            case 'c':
//                if(scanf("%d", &d1) != 1) { Error("c: bad deck"); }
//                d[d1] = deckCreate();
//                break;
//
//            case 'd':
//                if(scanf("%d", &d1) != 1) { Error("d: bad deck"); }
//                deckDestroy(d[d1]);
//                break;
//
//            case 'e':
//                if(scanf("%d", &d1) != 1) { Error("e: bad deck"); }
//                printf("%d\n", deckNotEmpty(d[d1]) != 0);
//                break;
//
//            case '-':
//                if(scanf("%d", &d1) != 1) { Error("-: bad deck"); }
//                c = deckGetCard(d[d1]);
//                printf("%c%c\n", c.rank, c.suit);
//                break;
//
//            case '+':
//                if(scanf("%d", &d1) != 1) { Error("+: bad deck"); }
//                if(scanf(" %c%c", &c.rank, &c.suit) != 2) { Error("+: bad card"); }
//                deckPutCard(d[d1], c);
//                break;
//
//            case '/':
//                if(scanf("%d", &d1) != 1) { Error("/: bad deck"); }
//                if(scanf("%d", &d2) != 1) { Error("/: bad deck"); }
//                if(scanf("%d", &n) != 1) { Error("/: bad n"); }
//                deckSplit(d[d1], n, &d[d1], &d[d2]);
//                break;
//
//            case '*':
//                if(scanf("%d", &d1) != 1) { Error("*: bad deck"); }
//                if(scanf("%d", &d2) != 1) { Error("*: bad deck"); }
//                d[d1] = deckShuffle(d[d1], d[d2]);
//                break;
//
//            case 'p':
//                if(scanf("%d", &d1) != 1) { Error("p: bad deck"); }
//                deckPrint(d[d1], stdout);
//                putchar('\n');
//                break;
//
//            case 'q':
//                exit(0);
//                break;
//
//            case '#':
//                // eat rest of line
//                while(((command = getchar()) != EOF) && (command != '\n'));
//                break;
//
//            default:
//                if(!isspace(command)) {
//                    fprintf(stderr, "%s: bad command %c\n", argv[0], command);
//                    exit(1);
//                }
//                // else ignore it
//                break;
//        }
//    }
//
//    // couldn't read a command!
//    Error("unexpected end of file");
//}

