#include <iostream>
#include <time.h>
#include <string>
#include <stdlib.h>

using namespace std;

// ---- GLOBAL VARIABLES ----
// console display
const string consoleSep = "-------------------------------";
const string consoleLine = "* * * * * *";
// game choices
const int NUM_VALID_GAMES = 1;
const int MAX_GAME_NAME = 100;
string validGameChoices[][MAX_GAME_NAME] = {{"1", "Go Fish"}};
// cards and decks
const int CARD_SIZE = 3;
const int NUM_SUITS = 4;
const int NUM_NUM_CARDS = 9;
const int NUM_FACE_CARDS = 4;
const int NUM_CARD_RANKS = NUM_NUM_CARDS + NUM_FACE_CARDS;
const int DECK_SIZE = NUM_SUITS * NUM_CARD_RANKS;
char** cardRanks = (char**)malloc(NUM_CARD_RANKS * sizeof(char));

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
    cout << "Please select a game to play: " << endl;
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
    return false;
}
void showGameChoice(string userChoice) {
    cout << "You chose to play " << validGameChoices[stoi(userChoice)-1][1] << "!\n";
    cout << "\n" << consoleSep << endl;
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
void addToDeck(char** deck, int n, char* card) { // UNTESTED
    deck = (char**)realloc(deck, n + CARD_SIZE * sizeof(char));
    deck[n] = copyCard(card);
}
bool checkValidCard(string s, char** userCards, int numUserCards, char** allCards, int n) { // DOES NOT WORK
    if (s.length() != 3) {
        return false;
    }
    bool valid = false;
    for (int i = 0; i < n; i++) {
        char* currCard = allCards[i];
        if (s[0] == currCard[0] && s[1] == currCard[1] && s[2] == currCard[2]) {
            printf("in allCards, s = %c%c%c, currCard = %c%c%c\n", s[0], s[1], s[2], currCard[0], currCard[1], currCard[2]);
            valid = true;
            break;
        }
    }
    cout << "check allCards, valid = " << valid << endl;
    if (!valid) {return false;}
//    printf("0 = %c%c%c, 1 = %c%c%c\n", userCards[0][0], userCards[0][1], userCards[0][2], userCards[1][0], userCards[1][1], userCards[1][2]);
    valid = false;
    for (int i = 0; i < numUserCards; i++) {
        char* currCard = userCards[i];
        if (s[0] == currCard[0] && s[1] == currCard[1] && s[2] == currCard[2]) {
            printf("\tin userCards at i = %d, currCard = %c%c%c\n", i, currCard[0], currCard[1], currCard[2]);
            cout << "userCards" << endl;
            printArray(userCards, numUserCards);
            valid = true;
            break;
        }
    }
    cout << "check userCards, valid = " << valid << endl;
    return valid;
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
bool cardsEq(char* c1, char* c2) {
    return c1[0] == c2[0] && c1[1] == c2[1] && c1[2] == c2[2];
}
bool cardRanksEq(char* c1, char* c2) {
    return c1[0] == c2[0] && c1[1] == c2[1];
}

// GO FISH
char* askForRank() {
    string userAsk;
    do {
        cout << "Ask the computer for a card rank: ";
        cin >> userAsk;
    } while (!checkValidCardRank(userAsk));
    char* cardRank = (char*)malloc((CARD_SIZE-1) * sizeof(char));
    cardRank[0] = userAsk[0], cardRank[1] = userAsk[1];
    return cardRank;
}
bool checkPersonHasRank(char** cards, int n, char* cardRank) {
    for (int i = 0; i < n; i++) {
        char* currCard = cards[i];
        if (cardRank[0] == currCard[0] && cardRank[1] == currCard[1]) {
            return true;
        }
    }
    return false;
}
int removeCardsWithRank(char** cards, int* n, char* cardRank) {
    int cardsRemoved = 0;
    int origN = *n;
    int i = 0;
    while (i < *n) {
        if (cardRanksEq(cards[i], cardRank)) {
            free(cards[i]);
            for (int j = i; j < origN-1-cardsRemoved; j++) {
                cards[j] = copyCard(cards[j+1]);
            }
            *n = *n - 1;
            cardsRemoved++;
        }
        i++;
    }
    return cardsRemoved;
}
void addToBooks(char** books, int* n, char* cardRank, int numToAdd) {
    int bookIdx = -1;
    for (int i = 0; i < *n; i++) {
        if (cardRanksEq(books[i], cardRank)) {
            bookIdx = i;
        }
    }
    if (bookIdx != -1) {
        int numCardsInBook = books[bookIdx][2] - '0';
        numCardsInBook += numToAdd;
        books[bookIdx][2] = to_string(numCardsInBook)[0];
    }
    else {
        books[*n] = (char*)malloc(CARD_SIZE * sizeof(char));
        books[*n][0] = cardRank[0], books[*n][1] = cardRank[1], books[*n][2] = to_string(numToAdd)[0];
        *n = *n + 1;
    }
}
void playGoFish(char** origCardDeck, int origDeckSize) {
    char** stock = copyDeck(origCardDeck, origDeckSize);
    int* stockSize = (int*)malloc(sizeof(int));
    *stockSize = DECK_SIZE;
    bool gameOver = false;
    const int BOOK_SIZE = 4;
    char** userBooks = (char**)malloc(sizeof(char*));
    char** compBooks = (char**)malloc(sizeof(char*));
    int* numUserCards = (int*)malloc(sizeof(int));
    int* numCompCards = (int*)malloc(sizeof(int));
    int* numUserBooks = (int*)malloc(sizeof(int));
    int* numCompBooks = (int*)malloc(sizeof(int));
    *numUserCards = 7, *numCompCards = 7;
    *numUserBooks = 0, *numCompBooks = 0;

    // deal cards
    char*** dealtCards = dealCards(stock, origDeckSize, 7);
    char** userCards = dealtCards[0];
    char** compCards = dealtCards[1];
    cout << "user's cards: " << endl;
    printArray(userCards, 7);
    cout << "computer's cards: " << endl;
    printArray(compCards, 7);

    while (!gameOver) {

        // user's turn
        printMessageBox("Your turn!");
        cout << "Your cards: " << endl;
        printArray(userCards, *numUserCards);
        char* userAsk = askForRank();
        cout << "You asked the Computer for: " << userAsk << endl;

        if (checkPersonHasRank(compCards, *numCompCards, userAsk)) {
            int numCardsToAdd = removeCardsWithRank(compCards, numCompCards, userAsk);
            cout << "numCardsToAdd = " << numCardsToAdd << endl;
            cout << "compCards" << endl;
            printArray(compCards, *numCompCards);
            cout << "userBooks" << endl;
            printArray(userBooks, *numUserBooks);
            addToBooks(userBooks, numUserBooks, userAsk, numCardsToAdd);
            removeCardsWithRank(userCards, numUserCards, userAsk);
            cout << "userBooks" << endl;
            printArray(userBooks, *numUserBooks);
        }
        else {
            // comp must go fish
        }

        // computer's turn
        printMessageBox("Computer's turn!");

        // clear stuff
        free(userAsk);
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

    // card suits and face cards
    char **cardSuits = (char**)malloc(NUM_SUITS * sizeof(char*));
    cardSuits[0] = "S", cardSuits[1] = "H", cardSuits[2] = "D", cardSuits[3] = "C";
    char **faceCards = (char**)malloc(NUM_FACE_CARDS * sizeof(char*));
    faceCards[0] = "J", faceCards[1] = "Q", faceCards[2] = "K", faceCards[3] = "A";

    // populating global cardRanks
    for (int i = 0; i < NUM_CARD_RANKS; i++) {
        cardRanks[i] = (char*)malloc((CARD_SIZE-1) * sizeof(char));
    }
    int cdRankCount = 0;
    for (int i = 2; i < 10; i++) {
        cardRanks[cdRankCount][0] = '0', cardRanks[cdRankCount][1] = to_string(i)[0];
        cdRankCount++;
    }
    cardRanks[cdRankCount][0] = '1', cardRanks[cdRankCount][1] = '0';
    cdRankCount++;
    for (int i = 0; i < NUM_FACE_CARDS; i++) {
        cardRanks[cdRankCount][0] = '0', cardRanks[cdRankCount][1] = faceCards[i][0];
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
        char currSuit = cardSuits[i][0];
        for (int j = 2; j < 10; j++) {
            fillCard(cardDeck[cdCount], '0', to_string(j)[0], currSuit);
            cdCount++;
        }
        fillCard(cardDeck[cdCount], '1', '0', currSuit);
        cdCount++;
        for (int j = 0; j < NUM_FACE_CARDS; j++) {
            fillCard(cardDeck[cdCount], '0', faceCards[j][0], currSuit);
            cdCount++;
        }
    }
    cout << "\ncardDeck" << endl;
    printArray(cardDeck, DECK_SIZE);

    // ---- PREP FOR GAME ----

    // shuffle deck
    srand(time(0));
    shuffleDeck(cardDeck, DECK_SIZE);
    cout << "\nshuffled deck" << endl;
    printArray(cardDeck,DECK_SIZE);

    // select game to play
    string userChoice = selectGame();
    while (!checkValidGameChoice(userChoice)) {
        cout << "Invalid choice" << endl;
        userChoice = selectGame();
    }
    showGameChoice(userChoice);

    // play game
    if (userChoice == "1") {
        playGoFish(cardDeck, DECK_SIZE);
    }
    else {
        cout << "Something went wrong :(" << endl;
        return -1;
    }

    // ---- END STUFF ----

    // deallocating memory
    free(cardSuits);
    free(faceCards);
    free(cardDeck);
    return 0;
}
