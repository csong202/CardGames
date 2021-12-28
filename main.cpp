#include <iostream>
#include <time.h>
//#include <string>

using namespace std;

void playGoFish() {

}
void shuffleDeck(string deck[], int n) {
    for (int i = 0; i < n; i++) {
        int random = rand() % n;
        string temp = deck[random];
        deck[random] = deck[i];
        deck[i] = temp;
    }
}
// testing utils
void printStrArray(string arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "\"" << arr[i] << "\" ";
//        cout << arr[i] << " ";
    }
    printf("\n");
}

int main()
{
    const int NUM_SUITS = 4;
    const int NUM_VALS = 13;
    const int DECK_SIZE = NUM_SUITS * NUM_VALS;

    const string cardSuits[NUM_SUITS] = {"S", "H", "D", "C"};
    const string cardValues[NUM_VALS] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    string cardDeck[DECK_SIZE];

    // create card deck
    int counter = 0;
    for (int i = 0; i < NUM_VALS; i++) {
        for (int j = 0; j < NUM_SUITS; j++) {
            cardDeck[counter] = cardValues[i] + cardSuits[j];
            counter++;
         }
    }

    // shuffle deck
    srand(time(0));
    printStrArray(cardDeck, DECK_SIZE);
    shuffleDeck(cardDeck, DECK_SIZE);
    printStrArray(cardDeck,DECK_SIZE);


    return 0;
}
