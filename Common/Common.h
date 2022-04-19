#pragma once

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
const string GAME_TIE = "";
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
char* const NULL_RANK = (char*)malloc(RANK_SIZE * sizeof(char));

// ---- FUNCTIONS ----

// testing utils
void printStrArray(string arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "\"" << arr[i] << "\" ";
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
void free2DArray(char** arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}
void free2DArray(char** arr, int* size) {
    free2DArray(arr, *size);
    free(size);
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
    if (winner != GAME_TIE && winner != COMP_NAME) {
        message = "CONGRATS, " + winner + "! You won!";
    }
    else if (winner != GAME_TIE && winner == COMP_NAME) {
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
string getUserName() {
    string userName;
    do {
        cout << "Please enter your name: ";
        cin >> userName;
    } while(userName.length() == 0 && userName != COMP_NAME);
    return userName;
}
void fillCard(char* card, char val1, char val2, char suit) {
    card[0] = val1, card[1] = val2, card[2] = suit;
}
char* copyCard(char* card) {
    char* copyCard = (char*)malloc(CARD_SIZE * sizeof(char));
    fillCard(copyCard, card[0], card[1], card[2]);
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
        copyDeck[i] = copyCard(deck[i]);
    }
    cout << "copied deck:" << endl;
    printArray(copyDeck, n);
    return copyDeck;
}
char*** dealCards(char** deck, int deckSize, int numToDeal) {
    char*** dealtCards = (char***)malloc(2 * sizeof(char**));
    for (int i = 0; i < 2; i++) {
        dealtCards[i] = (char**)malloc(CARD_SIZE * numToDeal * sizeof(char*));
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
    cards[*n-1] = copyCard(card);
    // cout << "just added cards" << endl;
    // printArray(cards, *n);
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
    int origN = *n;
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
    for (int k = origN-numRemoved; k < origN; k++) {
        free(cards[k]);
    }
    // cout << "toRemove" << endl;
    // printArray(toRemove, numToRemove);
    // cout << "just removed from cards" << endl;
    // printArray(cards, *n);
}
char* removeTopFromCards(char** cards, int* n) {
    char* toRemove = copyCard(cards[0]);
    char** temp = (char**)malloc(sizeof(char*));
    temp[0] = copyCard(toRemove);
    removeFromCards(cards, n, temp, 1);
    free2DArray(temp, 1);
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
bool rankInCards(char** cards, int n, char* cardRank) {
    for (int i = 0; i < n; i++) {
        // printf("cards[i] = %c%c%c\n", cards[i][0], cards[i][1], cards[i][2]);
        if (cardRanksEq(cards[i], cardRank)) {
            // printf("true\n");
            return true;
        }
    }
    // printf("%c%c not in cards\n", cardRank[0], cardRank[1]);
    return false;
}