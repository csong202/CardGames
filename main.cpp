#include <iostream>
#include <time.h>
#include <string>
#include <stdlib.h>

using namespace std;

const string consoleSep = "-------------------------------";
const string consoleLine = "* * * * * *";

// playing games
string selectGame() {
    string input;
    cout << "\n" << consoleLine << endl;
    cout << "Please select a game to play: " << endl;
    cout << "1. Go Fish" << endl;
    cin >> input;
    cout << consoleLine << "\n" << endl;
    return input;
}
void showGameChoice() {
    cout << "\n" << consoleSep << endl;
}
void playGoFish() {

}
// game functionalities
void shuffleDeck(string deck[], int n) {
    for (int i = 0; i < n; i++) {
        int random = rand() % n;
        string temp = deck[random];
        deck[random] = deck[i];
        deck[i] = temp;
    }
}
void shuffleDeck(char** deck, int n) {
    for (int i = 0; i < n; i++) {
        int random = rand() % n;
        char* temp = deck[random];
        deck[random] = deck[i];
        deck[i] = temp;
    }
}
// functional utils
void fillCard(char* card, char val1, char val2, char suit) {
    card[0] = val1, card[1] = val2, card[2] = suit;
//    cout << card[0] << card[1] << card[2] << " ";
}
bool checkValidGameChoice() {
    return false;
}
bool strArrayContains(string arr[], int n, string elem) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == elem) {
            return true;
        }
    }
    return false;
}
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
//
//    // select game to play
//    const int NUM_VALID_GAMES = 1;
//    string validChoices[] = {"1"};
////    string gameChoices[][] = {{"1", "Go Fish"}};
//    /*
//    idea: 2d array for valid choices, use in selectGame and showGameChoice
//    validChoices = [["1", "Go Fish"]]
//    */
//    string userChoice = selectGame();
//    while (!strArrayContains(validChoices, NUM_VALID_GAMES, userChoice)) {
//        cout << "Invalid choice" << endl;
//        userChoice = selectGame();
//    }
//
//    // play game
//    if (userChoice == "1") {
//        cout << "\n" << consoleSep << endl;
//        cout << "Playing Go Fish!" << endl;
//        playGoFish();
//    }
//    else {
//        cout << "something went wrong :(" << endl;
//        return -1;
//    }
    free(cardSuits);
    free(faceCards);
    free(cardDeck);
    return 0;
}
