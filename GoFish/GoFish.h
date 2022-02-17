#pragma once
#include "../precompiled_headers/pch.h"
#include "../Common/Common.h"

using namespace std;

bool canAskForRank(char** cards, int n, string userAsk) {
    char* cardRank = (char*)malloc(RANK_SIZE * sizeof(char));
    cardRank[0] = userAsk[0], cardRank[1] = userAsk[1];
    bool canAsk = rankInCards(cards, n, cardRank);
    if (!canAsk) {return false;}
    canAsk = checkValidCardRank(userAsk);
    return canAsk;
}
char* askForRank(char** cards, int n) {
    string userAsk;
    do {
        cout << "Ask the computer for (card rank): ";
        cin >> userAsk;
    } while (!canAskForRank(cards, n, userAsk));
    char* cardRank = (char*)malloc(RANK_SIZE * sizeof(char));
    cardRank[0] = userAsk[0], cardRank[1] = userAsk[1];
    return cardRank;
}
char* getCompAsk(char** compCards, int n, char** prevAsks, int numPrevAsks) {
    int random;
    char* compRank;
    do {
        random = rand() % NUM_CARD_RANKS;
        free(compRank);
        compRank = copyCardRank(cardRanks[random]);
    } while(!rankInCards(compCards, n, compRank) || rankInCards(prevAsks, numPrevAsks, compRank));
    return compRank;
}

int removeCardsWithRank(char** cards, int* n, char* cardRank) {
    int numToRemove = 0;
    char** toRemove = (char**)malloc(numToRemove * sizeof(char*));
    int idx = 0;
    for (int i = 0; i < *n; i++) {
        if (cardRanksEq(cards[i], cardRank)) {
            numToRemove++;
            toRemove = (char**)realloc(toRemove, numToRemove * sizeof(char*));
            toRemove[idx] = copyCard(cards[i]);
            idx++;
        }
    }
    removeFromCards(cards, n, toRemove, numToRemove);
    return numToRemove;
}
void giveCardsWithRank(char** pCards, int* nP, char** opCards, int* opN, char* cardRank) {
    for (int i = 0; i < *opN; i++) {
        if (cardRanksEq(opCards[i], cardRank)) {
            addToCards(pCards, nP, opCards[i]);
        }
    }
    removeCardsWithRank(opCards, opN, cardRank);
}

void addToBooks(char** books, int* n, char* cardRank) {
    *n = *n+1;
    // books = (char**)realloc(books, (*n) * sizeof(char*));
    books[*n-1] = copyCardRank(cardRank);
}
void handleBookInCards(char** cards, int* n, char** books, int* numBooks, char* cardRank) {
    bool done = false;
    int i;
    char* cardRankCopy = copyCardRank(cardRank);
    while (!done) {
        for (i = 0; i < *n; i++) {
            if (cardRanksEq(cardRank, NULL_RANK)) {
                free(cardRankCopy);
                cardRankCopy = copyCardRank(cards[i]);
            }
            int numCardsToAdd = countCardsWithRank(cards, *n, cardRankCopy);
            if (numCardsToAdd == NUM_SUITS) {
                if (!cardRanksEq(cardRankCopy, NULL_RANK)) {
                    done = true;
                    removeCardsWithRank(cards, n, cardRankCopy);
                    addToBooks(books, numBooks, cardRankCopy);
                    cout << "books:" << endl;
                    printArray(books, *numBooks);
                }
                break;
            }
        } 
        if (i >= *n-1) {done = true;}
    }
    free(cardRankCopy);    
}

char* goFish(char** cards, int* n, char** stock, int* stockSize) {
    char* newCard = removeTopFromCards(stock, stockSize);
    cout << "newCard = " << newCard << endl;
    addToCards(cards, n, newCard);
    cout << "stock: " << endl;
    printArray(stock, *stockSize);
    cout << "cards: " << endl;
    printArray(cards, *n);
    return newCard;
}

bool checkWinConditionGoFish(int numUserBooks, int numCompBooks, int stockSize) {
    return stockSize == 0 || (numUserBooks + numCompBooks == NUM_CARD_RANKS);
}

// ---- PLAYING GO FISH ----

void playGoFish(char** origCardDeck, int origDeckSize) {
    char** stock = copyDeck(origCardDeck, origDeckSize);
    cout << "just made stock" << endl;
    int* stockSize = (int*)malloc(sizeof(int));
    *stockSize = DECK_SIZE;
    bool gameOver = false;
    char** userBooks = (char**)malloc(sizeof(char*));
    char** compBooks = (char**)malloc(sizeof(char*));
    int* numUserCards = (int*)malloc(sizeof(int));
    int* numCompCards = (int*)malloc(sizeof(int));
    int* numUserBooks = (int*)malloc(sizeof(int));
    int* numCompBooks = (int*)malloc(sizeof(int));
    const int DEAL_SIZE = 20;
    *numUserCards = DEAL_SIZE, *numCompCards = DEAL_SIZE;
    *numUserBooks = 0, *numCompBooks = 0;
    char** compPrevAsks = (char**)malloc(sizeof(char*));
    int* numPrevAsks = (int*)malloc(sizeof(int));
    *numPrevAsks = 0;

    // get name
    // string userName = getUserName();
    /* TESTING PURPOSES */
    string userName = "player";

    // deal cards
    char*** dealtCards = dealCards(stock, origDeckSize, DEAL_SIZE);
    char** userCards = dealtCards[0];
    char** compCards = dealtCards[1];
    cout << "user's cards: " << endl;
    printArray(userCards, *numUserCards);
    cout << "computer's cards: " << endl;
    printArray(compCards, *numCompCards);
    removeFromCards(stock, stockSize, userCards, *numUserCards);
    removeFromCards(stock, stockSize, compCards, *numCompCards);
    cout << "stock: " << endl;
    printArray(stock, *stockSize);
    handleBookInCards(userCards, numUserCards, userBooks, numUserBooks, NULL_RANK);
    handleBookInCards(compCards, numCompCards, compBooks, numCompBooks, NULL_RANK);

    bool compTurnAgain = false;
    while (!gameOver) {
        // user's turn
        if (!compTurnAgain) {
            printMessageBox("Your turn!");
            cout << "Your cards: " << endl;
            printArray(userCards, *numUserCards);
            char* userAsk = askForRank(userCards, *numUserCards);

            if (*numUserCards > 0 && rankInCards(compCards, *numCompCards, userAsk)) {
                giveCardsWithRank(userCards, numUserCards, compCards, numCompCards, userAsk);
                cout << "Your cards: " << endl;
                printArray(userCards, *numUserCards);
                handleBookInCards(userCards, numUserCards, userBooks, numUserBooks, userAsk);
                cout << "Your cards after handling books: " << endl;
                printArray(userCards, *numUserCards);
                if (!checkWinConditionGoFish(*numUserBooks, *numCompBooks, *stockSize)) {
                    continue;
                } else {
                    break;
                }
            }
            else {
                cout << "Go Fish!" << endl;
                char* newCard = goFish(userCards, numUserCards, stock, stockSize);
                handleBookInCards(userCards, numUserCards, userBooks, numUserBooks, newCard);
                cout << "Your cards after handling books: " << endl;
                printArray(userCards, *numUserCards);
                if (cardRanksEq(newCard, userAsk) && !checkWinConditionGoFish(*numUserBooks, *numCompBooks, *stockSize)) {
                    continue;
                } else if (checkWinConditionGoFish(*numUserBooks, *numCompBooks, *stockSize)) {
                    break;
                }
            }
            free(userAsk);
        }    

        // computer's turn
        printMessageBox("Computer's turn!");
        cout << "compCards" << endl;
        printArray(compCards, *numCompCards);
        char* compAsk = getCompAsk(compCards, *numCompCards, compPrevAsks, *numPrevAsks);
        cout << "Computer asked for: " << compAsk << "'s" << endl;

        if (*numCompCards > 0 && rankInCards(userCards, *numUserCards, compAsk)) {
            giveCardsWithRank(compCards, numCompCards, userCards, numUserCards, compAsk);
            cout << "Computer's cards: " << endl;
            printArray(compCards, *numCompCards);
            handleBookInCards(compCards, numCompCards, compBooks, numCompBooks, compAsk);
            cout << "Computer's cards after handling books: " << endl;
            printArray(compCards, *numCompCards);
            compTurnAgain = true;
        }
        else {
            cout << "Computer must Go Fish!" << endl;
            char* newCard = goFish(compCards, numCompCards, stock, stockSize);
            handleBookInCards(compCards, numCompCards, compBooks, numCompBooks, copyCardRank(newCard));
            cout << "Computer's cards after handling books: " << endl;
            printArray(compCards, *numCompCards);
            compTurnAgain = cardRanksEq(newCard, compAsk);
        }
        if (compTurnAgain) {
            compPrevAsks = (char**)realloc(compPrevAsks, (*numPrevAsks+1) * sizeof(char*));
            compPrevAsks[*numPrevAsks] = copyCardRank(compAsk);
            *numPrevAsks = *numPrevAsks + 1;
            cout << "compPrevAsks: " << endl;
            printArray(compPrevAsks, *numPrevAsks);
        }
        else {
            free2DArray(compPrevAsks, *numPrevAsks);
            *numPrevAsks = 0;
            printArray(compPrevAsks, *numPrevAsks);
        }

        gameOver = checkWinConditionGoFish(*numUserBooks, *numCompBooks, *stockSize);
    }

    string winner;
    if (*numUserBooks > *numCompBooks) {
        winner = userName;
    }
    else if (*numCompBooks > *numUserBooks) {
        winner = COMP_NAME;
    }
    else {
        winner = GAME_TIE;
    }
    displayWinner(winner);

    // deallocate memory
    free2DArray(stock, stockSize);
    free2DArray(userBooks, numUserBooks);
    free2DArray(compBooks, numCompBooks);
    free2DArray(userCards, numUserCards);
    free2DArray(compCards, numCompCards);
    free2DArray(compPrevAsks, numPrevAsks);
}