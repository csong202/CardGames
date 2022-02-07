#include "precompiled_headers/pch.h"
#include "Common/Common.h"
#include "GoFish/GoFish.h"

/*
TO DO TESTING
- winning game
- running out of cards
*/

using namespace std;

int main()
{
    // ---- CREATING CARD DECK ----

    // populating global NULL_RANK
    NULL_RANK[0] = '0', NULL_RANK[1] = '0';

    // populating global cardSuits and faceCards
    cardSuits[0] = 'S', cardSuits[1] = 'H', cardSuits[2] = 'D', cardSuits[3] = 'C';
    faceCards[0] = 'J', faceCards[1] = 'Q', faceCards[2] = 'K', faceCards[3] = 'A';

    // populating global cardRanks
    for (int i = 0; i < NUM_CARD_RANKS; i++) {
        cardRanks[i] = (char*)malloc(RANK_SIZE * sizeof(char));
    }
    int cdRankCount = 0;
    for (int i = 2; i < 10; i++) {
        cardRanks[cdRankCount][0] = '0', cardRanks[cdRankCount][1] = to_string(i)[0];
        cdRankCount++;
    }
    cardRanks[cdRankCount][0] = '1', cardRanks[cdRankCount][1] = '0';
    cdRankCount++;
    for (int i = 0; i < NUM_FACE_CARDS; i++) {
        cardRanks[cdRankCount][0] = '0', cardRanks[cdRankCount][1] = faceCards[i];
        cdRankCount++;
    }

    // creating card deck
    char **cardDeck = (char**)malloc(DECK_SIZE * sizeof(char*));
    if (cardDeck == NULL) {
        cout << "no more space" << endl;
        return -1;
    }
    for (int i = 0; i < DECK_SIZE; i++) {
        cardDeck[i] = (char*)malloc(3 * sizeof(char));
    }
    int cdCount = 0;
    for (int i = 0; i < NUM_SUITS; i++) {
        char currSuit = cardSuits[i];
        for (int j = 2; j < 10; j++) {
            fillCard(cardDeck[cdCount], '0', to_string(j)[0], currSuit);
            cdCount++;
        }
        fillCard(cardDeck[cdCount], '1', '0', currSuit);
        cdCount++;
        for (int j = 0; j < NUM_FACE_CARDS; j++) {
            fillCard(cardDeck[cdCount], '0', faceCards[j], currSuit);
            cdCount++;
        }
    }
    cout << "\ncardDeck" << endl;
    printArray(cardDeck, DECK_SIZE);

    // ---- PREP FOR GAME ----
    string userChoice;
    do {
        // shuffle deck
        srand(time(0));
        shuffleDeck(cardDeck, DECK_SIZE);
        cout << "\nshuffled deck" << endl;
        printArray(cardDeck,DECK_SIZE);

        // // select game to play
        // userChoice = selectGame();
        // while (!checkValidGameChoice(userChoice)) {
        //     cout << "Invalid choice" << endl;
        //     userChoice = selectGame();
        // }
        // showGameChoice(userChoice);
        /* TESTING PURPOSES */
        userChoice = "1";

        // play game
        if (userChoice == "1") {
            playGoFish(cardDeck, DECK_SIZE);
        }
        else if (userChoice == QUIT_PROG_CMD) {
            cout << "Goodbye!" << endl;
            break;
        }
        else {
            cout << "Something went wrong :(" << endl;
            return -1;
        }
    } while (userChoice != QUIT_PROG_CMD);

    // ---- END STUFF ----

    // deallocating memory
    free(cardSuits);
    free(faceCards);
    free2DArray(cardDeck, DECK_SIZE);
    return 0;
}
