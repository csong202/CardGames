#include <iostream>
//#include <string>

using namespace std;

void playGoFish() {

}
void printStrArray(string arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    printf("\n");
}

int main()
{
    const string cardSuits[4] = {"S", "H", "D", "C"};
    const string cardValues[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    string cardDeck[56];
    int counter = 0;
    printf("%d %d\n", sizeof(cardValues), sizeof(cardSuits));
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            cardDeck[counter] = cardValues[i] + cardSuits[j];
            counter++;
         }
    }
    printStrArray(cardDeck, 56);

    return 0;
}
