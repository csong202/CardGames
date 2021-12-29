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
// game functionalities
void fillCard(char* card, char val1, char val2, char suit) {
    card[0] = val1, card[1] = val2, card[2] = suit;
//    cout << card[0] << card[1] << card[2] << " ";
}
char* copyCard(char* card) {
    char* copyCard = (char*)malloc(3 * sizeof(char));
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
bool checkValidGameChoice(string userChoice) {
    for (int i = 0; i < NUM_VALID_GAMES; i++) {
        if (validGameChoices[i][0] == userChoice) {
            return true;
        }
    }
    return false;
}
char** copyDeck(char** deck, int n) {
    char **copyDeck = (char**)malloc(n * sizeof(char*));
    if (copyDeck == NULL) {
        cout << "no more space" << endl;
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        copyDeck[i] = (char*)malloc(3 * sizeof(char));
        fillCard(copyDeck[i], deck[i][0], deck[i][1], deck[i][2]);
    }
    printArray(copyDeck, n);
    return copyDeck;
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
void showGameChoice(string userChoice) {
    cout << "You chose to play " << validGameChoices[stoi(userChoice)-1][1] << "!\n";
    cout << "\n" << consoleSep << endl;
}
// common game utils
char*** dealCards(char** deck, int deckSize, int numToDeal) {
    char*** dealtCards = (char***)malloc(2 * sizeof(char**));
    for (int i = 0; i < 2; i++) {
        dealtCards[i] = (char**)malloc(3 * numToDeal * sizeof(char*));
        for (int j = 0; j < numToDeal; j++) {
            dealtCards[i][j] = (char*)malloc(3 * sizeof(char));
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

// GO FISH
void playGoFish(char** origCardDeck, int origDeckSize) {
    char** stock = copyDeck(origCardDeck, origDeckSize);

    // deal cards
    char*** dealtCards = dealCards(stock, origDeckSize, 7);
    char** userCards = dealtCards[0];
    char** compCards = dealtCards[1];
    cout << "user's cards: " << endl;
    printArray(userCards, 7);
    cout << "computer's cards: " << endl;
    printArray(compCards, 7);
}


int main()
{
    // ---- CONSTANTS ----
    const int NUM_SUITS = 4;
    const int NUM_NUM_CARDS = 9;
    const int NUM_FACE_CARDS = 4;
    const int NUM_VALS = NUM_NUM_CARDS + NUM_FACE_CARDS;
    const int DECK_SIZE = NUM_SUITS * NUM_VALS;

    // ---- CREATING CARD DECK ----

    // card suits and face cards
    char **cardSuits = (char**)malloc(NUM_SUITS * sizeof(char*));
    cardSuits[0] = "S", cardSuits[1] = "H", cardSuits[2] = "D", cardSuits[3] = "C";
    char **faceCards = (char**)malloc(NUM_FACE_CARDS * sizeof(char*));
    faceCards[0] = "J", faceCards[1] = "Q", faceCards[2] = "K", faceCards[3] = "A";

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
