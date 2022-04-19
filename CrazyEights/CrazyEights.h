#pragma once
#include "../precompiled_headers/pch.h"
#include "../Common/Common.h"

using namespace std;

// ---- GAME FUNCTIONS ----
bool canPlayCard(char* lastCard, char* newCard) {
    return cardRanksEq(lastCard, newCard) || cardSuitsEq(lastCard, newCard);
}


// ---- PLAYING CRAZY EIGHTS ----
void playCrazyEights(char** stock) {
    bool gameOver = false;

    const int DEAL_SIZE = 5;
    int* stockSize = new int(DECK_SIZE);

    char*** dealtCards = dealCards(stock, stockSize, DEAL_SIZE);
    char** userCards = dealtCards[0];
    char** compCards = dealtCards[1];
    int* numUserCards = new int(DEAL_SIZE);
    int* numCompCards = new int(DEAL_SIZE);
    
    char* lastCardPlayed = new char[CARD_SIZE];

    while (!gameOver) {
        char* starterCard = removeTopFromCards(stock, stockSize);
        lastCardPlayed = starterCard;

        printf("starter card is %c%c%c\n", starterCard[0], starterCard[1], starterCard[2]);

        // user's turn
        char* userPlay;
        do {
            userPlay = chooseCardFromHand(userCards, numUserCards);
        } while (!canPlayCard(lastCardPlayed, userPlay));
        removeSingleCard(userCards, numUserCards, userPlay);
        printf("you chose to play %c%c%c\n", userPlay[0], userPlay[1], userPlay[2]);
    }
}