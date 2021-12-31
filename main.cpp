#include <iostream>
#include <time.h>
#include <string>
#include <stdlib.h>

/*
Run: f6
Run in external console: f8
*/

/*
TO DO TESTING
- winning game
- running out of cards
- handleBookInCards: starting with a book
*/

using namespace std;

// ---- GLOBAL VARIABLES ----
// console display
const string consoleSep = "-------------------------------";
const string consoleLine = "* * * * * *";
// game selection
const int NUM_VALID_GAMES = 1;
const int MAX_GAME_NAME = 50;
string validGameChoices[][MAX_GAME_NAME] = {{"1", "Go Fish"}};
const string QUIT_PROG_CMD = "Q";
// game play
const string COMP_NAME = "Computer";
// cards and decks
const int CARD_SIZE = 3;
const int RANK_SIZE = CARD_SIZE - 1;
const int NUM_SUITS = 4;
const int NUM_NUM_CARDS = 9;
const int NUM_FACE_CARDS = 4;
const int NUM_CARD_RANKS = NUM_NUM_CARDS + NUM_FACE_CARDS;
const int DECK_SIZE = NUM_SUITS * NUM_CARD_RANKS;
char* cardSuits = (char*)malloc(NUM_SUITS * sizeof(char));
char* faceCards = (char*)malloc(NUM_FACE_CARDS * sizeof(char));
char** cardRanks = (char**)malloc(NUM_CARD_RANKS * sizeof(char));
char* NULL_RANK = (char*)malloc(RANK_SIZE * sizeof(char));

// ---- FUNCTIONS ----

// testing utils
void printStrArray(string arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "\"" << arr[i] << "\" ";
//        cout << arr[i] << " ";
    }
    printf("\n");
}
void printArray(char** ptr, int n) {
    for (int i = 0; i < n; i++) {
        cout << *(ptr+i) << " ";
    }
//    printf("\narray size = %d\n", n);
    printf("\n");
}

// functional utils
bool strArrayContains(string arr[], int n, string elem) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == elem) {
            return true;
        }
    }
    return false;
}
void printMessageBox(string message) {
    printf("\n");
    int length = message.length() + 4;
    string border = string(length, '*');
    cout << border << endl;
    cout << "* " << message << " *" << endl;
    cout << border << endl;
}

// PLAYING GAMES
// game selection
string selectGame() {
    string input;
    cout << "\n" << consoleLine << endl;
    cout << "Please select a game to play or enter Q to quit: " << endl;
    for (int i = 1; i < NUM_VALID_GAMES + 1; i++) {
        cout << i << ". " << validGameChoices[i-1][1] << endl;
    }
    cin >> input;
    cout << consoleLine << "\n" << endl;
    return input;
}
bool checkValidGameChoice(string userChoice) {
    for (int i = 0; i < NUM_VALID_GAMES; i++) {
        if (validGameChoices[i][0] == userChoice) {
            return true;
        }
    }
    return userChoice == QUIT_PROG_CMD;
}
void showGameChoice(string userChoice) {
    if (userChoice != QUIT_PROG_CMD) {
        cout << "You chose to play " << validGameChoices[stoi(userChoice)-1][1] << "!\n";
    }
    else {
        cout << "Exiting program" << endl;
        return;
    }
    cout << "\n" << consoleSep << endl;
}
void displayWinner(string winner) {
    string message;
    if (winner != "" && winner != COMP_NAME) {
        message = "CONGRATS, " + winner + "! You won!";
    }
    else if (winner != "" && winner == COMP_NAME) {
        message = "Oh no! You lost to " + COMP_NAME + " :(";
    }
    else {
        message = "There was a tie!";
    }
    int length = message.length() + 6;

    printf("\n");
    string border = string(length, '*');
    cout << border << endl;
    printf("\n");
    cout << "*  " << message << "  *" << endl;
    printf("\n");
    cout << border << endl;
}
// common game utils
void fillCard(char* card, char val1, char val2, char suit) {
    card[0] = val1, card[1] = val2, card[2] = suit;
}
char* copyCard(char* card) {
    char* copyCard = (char*)malloc(CARD_SIZE * sizeof(char));
    copyCard[0] = card[0], copyCard[1] = card[1], copyCard[2] = card[2];
    return copyCard;
}
char* copyCardRank(char* cardRank) {
    char* copyCR = (char*)malloc(RANK_SIZE * sizeof(char));
    copyCR[0] = cardRank[0], copyCR[1] = cardRank[1];
    return copyCR;
}
void shuffleDeck(char** deck, int n) {
    for (int i = 0; i < n; i++) {
        int random = rand() % n;
        char* temp = deck[random];
        deck[random] = deck[i];
        deck[i] = temp;
    }
}
char** copyDeck(char** deck, int n) {
    char **copyDeck = (char**)malloc(n * sizeof(char*));
    if (copyDeck == NULL) {
        cout << "no more space" << endl;
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        copyDeck[i] = (char*)malloc(CARD_SIZE * sizeof(char));
        copyDeck[i] = copyCard(deck[i]);
    }
    printArray(copyDeck, n);
    return copyDeck;
}
char*** dealCards(char** deck, int deckSize, int numToDeal) {
    char*** dealtCards = (char***)malloc(2 * sizeof(char**));
    for (int i = 0; i < 2; i++) {
        dealtCards[i] = (char**)malloc(CARD_SIZE * numToDeal * sizeof(char*));
        for (int j = 0; j < numToDeal; j++) {
            dealtCards[i][j] = (char*)malloc(CARD_SIZE * sizeof(char));
        }
    }
    int p1 = 0, p2 = 0;
    for (int i = 0; i < 2*numToDeal; i++) {
        if (i%2 == 0) {
            dealtCards[0][p1] = copyCard(deck[i]);
            p1++;
        }
        else {
            dealtCards[1][p2] = copyCard(deck[i]);
            p2++;
        }
    }
    return dealtCards;
}
void addToCards(char** cards, int* n, char* card) {
    *n = *n + 1;
    cards = (char**)realloc(cards, (*n) * sizeof(char*));
    cards[*n-1] = (char*)malloc(CARD_SIZE * sizeof(char));
    cards[*n-1] = copyCard(card);
}
bool checkValidCardRank(string r) {
    if (r.length() != 2) {
        return false;
    }
    for (int i = 0; i < NUM_CARD_RANKS; i++) {
        char* currRank = cardRanks[i];
        if (r[0] == currRank[0] && r[1] == currRank[1]) {
            return true;
        }
    }
    return false;
}
bool cardRanksEq(char* c1, char* c2) {
    return c1[0] == c2[0] && c1[1] == c2[1];
}
bool cardsEq(char* c1, char* c2) {
    return cardRanksEq(c1, c2) && c1[2] == c2[2];
}
void removeFromCards(char** cards, int* n, char** toRemove, int numToRemove) {
    int i = 0, j = 0;
    int numRemoved = 0;
    while (numRemoved < numToRemove && i < *n) {
        if (cardsEq(cards[i], toRemove[j])) {
            for (int k = i; k < *n-1; k++) {
                cards[k] = copyCard(cards[k+1]);
            }
            *n = *n - 1;
            numRemoved++;
            j++;
        }
        else {
            i++;
        } 
    }
}
char* removeTopFromCards(char** cards, int* n) {
    char* toRemove = (char*)malloc(CARD_SIZE * sizeof(char));
    toRemove = copyCard(cards[0]);
    char** temp = (char**)malloc(sizeof(char*));
    temp[0] = (char*)malloc(CARD_SIZE * sizeof(char));
    temp[0] = copyCard(toRemove);
    removeFromCards(cards, n, temp, 1);
    free(temp);
    return toRemove;
}
int countCardsWithRank(char** cards, int n, char* cardRank) {
    int numCards = 0;
    for (int i = 0; i < n; i++) {
        if (cardRanksEq(cards[i], cardRank)) {
            numCards++;
        }
    }
    return numCards;
}

// GO FISH
bool checkPersonHasRank(char** cards, int n, char* cardRank) {
    for (int i = 0; i < n; i++) {
        if (cardRanksEq(cards[i], cardRank)) {
            return true;
        }
    }
    return false;
}
bool canAskForRank(char** cards, int n, string userAsk) {
    char* cardRank = (char*)malloc(RANK_SIZE * sizeof(char));
    cardRank[0] = userAsk[0], cardRank[1] = userAsk[1];
    bool canAsk = checkPersonHasRank(cards, n, cardRank);
    if (!canAsk) {return false;}
    canAsk = checkValidCardRank(userAsk);
    return canAsk;
}
char* askForRank(char** cards, int n) {
    string userAsk;
    do {
        cout << "Ask the computer for a card rank: ";
        cin >> userAsk;
    } while (!canAskForRank(cards, n, userAsk));
    char* cardRank = (char*)malloc(RANK_SIZE * sizeof(char));
    cardRank[0] = userAsk[0], cardRank[1] = userAsk[1];
    return cardRank;
}
char* getCompAsk(char** cards, int n) {
    int random;
    char* compRank = (char*)malloc(RANK_SIZE * sizeof(char));
    do {
        random = rand() % NUM_CARD_RANKS;
        compRank = copyCardRank(cardRanks[random]);
    } while(!checkPersonHasRank(cards, n, compRank));
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
            toRemove[idx] = (char*)malloc(CARD_SIZE * sizeof(char));
            toRemove[idx] = copyCard(cards[i]);
            idx++;
        }
    }
    removeFromCards(cards, n, toRemove, numToRemove);
    return numToRemove;
}
void giveCardsWithRank(char** pCards, int* nP, char** opCards, int* opN, char* cardRank) {
    char** toRemove = (char**)malloc(sizeof(char*));
    int numToRemove = 0;
    for (int i = 0; i < *opN; i++) {
        if (cardRanksEq(opCards[i], cardRank)) {
            addToCards(pCards, nP, opCards[i]);
            toRemove = (char**)realloc(toRemove, (numToRemove+1) * sizeof(char*));
            toRemove[numToRemove] = (char*)malloc(CARD_SIZE * sizeof(char));
            toRemove[numToRemove] = copyCard(opCards[i]);
            numToRemove++;
        }
    }
    removeFromCards(opCards, opN, toRemove, numToRemove);
}
void addToBooks(char** books, int* n, char* cardRank) {
    books[*n] = (char*)malloc(RANK_SIZE * sizeof(char));
    books[*n] = copyCardRank(cardRank);
    *n = *n + 1;
}
void handleBookInCards(char** cards, int* n, char** books, int* numBooks, char* cardRank) {
    bool done = false;
    int i;
    while (!done) {
        for (i = 0; i < *n; i++) {
            if (cardRanksEq(cardRank, NULL_RANK)) {
                cardRank = copyCardRank(cards[i]);
            }
            int numCardsToAdd = countCardsWithRank(cards, *n, cardRank);
            if (numCardsToAdd == NUM_SUITS) {
                if (!cardRanksEq(cardRank, NULL_RANK)) {
                    done = true;
                    printf("i = %d, *n = %d\n", i, *n);
                    removeCardsWithRank(cards, n, cardRank);
                    addToBooks(books, numBooks, cardRank);
                    cout << "books" << endl;
                    printArray(books, *numBooks);
                    break;
                }
                break;
            }
        } 
        if (i >= *n-1) {done = true;}
    }    
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
void playGoFish(char** origCardDeck, int origDeckSize) {
    char** stock = copyDeck(origCardDeck, origDeckSize);
    int* stockSize = (int*)malloc(sizeof(int));
    *stockSize = DECK_SIZE;
    bool gameOver = false;
    char** userBooks = (char**)malloc(sizeof(char*));
    char** compBooks = (char**)malloc(sizeof(char*));
    int* numUserCards = (int*)malloc(sizeof(int));
    int* numCompCards = (int*)malloc(sizeof(int));
    int* numUserBooks = (int*)malloc(sizeof(int));
    int* numCompBooks = (int*)malloc(sizeof(int));
    const int DEAL_SIZE = 7;
    *numUserCards = DEAL_SIZE, *numCompCards = DEAL_SIZE;
    *numUserBooks = 0, *numCompBooks = 0;

    // get name
    string userName;
    do {
        cout << "Please enter your name: ";
        cin >> userName;
    } while(userName.length() == 0);

    // deal cards
    char*** dealtCards = dealCards(stock, origDeckSize, 7);
    char** userCards = dealtCards[0];
    char** compCards = dealtCards[1];
    cout << "user's cards: " << endl;
    printArray(userCards, 7);
    cout << "computer's cards: " << endl;
    printArray(compCards, 7);
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

            if (*numUserCards > 0 && checkPersonHasRank(compCards, *numCompCards, userAsk)) {
                int numCardsToAdd = countCardsWithRank(compCards, *numCompCards, userAsk)
                    + countCardsWithRank(userCards, *numUserCards, userAsk);
                if (numCardsToAdd == NUM_SUITS) {
                    removeCardsWithRank(userCards, numUserCards, userAsk);
                    removeCardsWithRank(compCards, numCompCards, userAsk);
                    addToBooks(userBooks, numUserBooks, userAsk);
                    cout << "userBooks" << endl;
                    printArray(userBooks, *numUserBooks);
                }
                else {
                    giveCardsWithRank(userCards, numUserCards, compCards, numCompCards, userAsk);
                }
                continue;
            }
            else {
                cout << "Go Fish!" << endl;
                char* newCard = goFish(userCards, numUserCards, stock, stockSize);
                handleBookInCards(userCards, numUserCards, userBooks, numUserBooks, copyCardRank(newCard));
                if (cardRanksEq(newCard, userAsk)) {continue;}
            }
            free(userAsk);
        }    

        // computer's turn
        printMessageBox("Computer's turn!");
        cout << "compCards" << endl;
        printArray(compCards, *numCompCards);
        char* compAsk = getCompAsk(compCards, *numCompCards);
        cout << "compAsk = " << compAsk << endl;

        if (*numCompCards > 0 && checkPersonHasRank(userCards, *numUserCards, compAsk)) {
            int numCardsToAdd = countCardsWithRank(compCards, *numCompCards, compAsk)
                + countCardsWithRank(userCards, *numUserCards, compAsk);
            if (numCardsToAdd == NUM_SUITS) {
                removeCardsWithRank(userCards, numUserCards, compAsk);
                removeCardsWithRank(compCards, numCompCards, compAsk);
                addToBooks(compBooks, numCompBooks, compAsk);
                cout << "compBooks" << endl;
                printArray(compBooks, *numCompBooks);
            }
            else {
                giveCardsWithRank(compCards, numCompCards, userCards, numUserCards, compAsk);
            }
            compTurnAgain = true;
        }
        else {
            cout << "Computer must Go Fish!" << endl;
            char* newCard = goFish(compCards, numCompCards, stock, stockSize);
            handleBookInCards(compCards, numCompCards, compBooks, numCompBooks, copyCardRank(newCard));
            compTurnAgain = cardRanksEq(newCard, compAsk);
        }
        free(compAsk);

        // winning condition
        gameOver = *stockSize == 0 || (*numUserBooks + *numCompBooks == NUM_CARD_RANKS);
    }

    string winner;
    if (*numUserBooks > *numCompBooks) {
        winner = userName;
    }
    else if (*numCompBooks > *numUserBooks) {
        winner = COMP_NAME;
    }
    else {
        winner = "";
    }

    // clear stuff
    free(stock);
    free(userBooks);
    free(compBooks);
    free(numUserBooks);
    free(numCompBooks);
    free(userCards);
    free(compCards);
    free(numUserCards);
    free(numCompCards);
}


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

        // select game to play
        userChoice = selectGame();
        while (!checkValidGameChoice(userChoice)) {
            cout << "Invalid choice" << endl;
            userChoice = selectGame();
        }
        showGameChoice(userChoice);

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
    free(cardDeck);
    return 0;
}
