#include <iostream>
#include "MemoryGame.hpp"
#include <cstdlib> 
#include <time.h>
#include <iomanip>

using namespace std;

void printSeparatedLine(int size);
MemoryGame::MemoryGame() {
    numPairs = 3;
    numSlots = 8;
    values = new string[numSlots];
    bShown = new bool[numSlots];

    // Generate three random integers in [0, 999]
    int random1 = rand() % 1000;
    int random2 = rand() % 1000;
    int random3 = rand() % 1000;

    // Place the random integers in pairs in the values array
    for (int i = 0; i < numSlots; i += 2) {
        if (i < 2) {
            values[i] = to_string(random1);
            values[i + 1] = to_string(random1);
            bShown[i] = false;
            bShown[i + 1] = false;
        } else if (i < 4) {
            values[i] = to_string(random2);
            values[i + 1] = to_string(random2);
            bShown[i] = false;
            bShown[i + 1] = false;
        } else {
            values[i] = to_string(random3);
            values[i + 1] = to_string(random3);
            bShown[i] = false;
            bShown[i + 1] = false;
        }
    }

    // Set the rest of the elements of values to be empty strings
    for (int i = 6; i < numSlots; i++) {
        values[i] = "";
        bShown[i] = false;
    }
    //rounds = 1; // Initialize rounds counter
}

MemoryGame::MemoryGame(int numPairs, int numSlots) {
    if (numPairs <= 0 || numSlots <= 0 || numSlots < 2 * numPairs) {
        // Default values if parameters are invalid
        numPairs = 3;
        numSlots = 8;
    }

    this->numPairs = numPairs;
    this->numSlots = numSlots;
    values = new string[numSlots];
    bShown = new bool[numSlots];

    // Generate numPairs random integers in [0, 999]
    for (int i = 0; i < numPairs; i++) {
        int random = rand() % 1000;
        for (int j = 0; j < 2; j++) {
            values[i * 2 + j] = to_string(random);
            bShown[i * 2 + j] = false;
        }
    }

    // Set the rest of the elements of values to be empty strings
    for (int i = numPairs * 2; i < numSlots; i++) {
        values[i] = "";
        bShown[i] = false;
    }
}

MemoryGame::MemoryGame(string* words, int size, int numSlots) {
    // Adjust numSlots if necessary
    if (size <= 0 || numSlots <= 0 || numSlots < 2 * size) {
        numSlots = 2 * size;
    }

    // Set data members numPairs and numSlots
    numPairs = size;
    this->numSlots = numSlots;

    // Allocate dynamic memory for values and bShown
    values = new string[numSlots];
    bShown = new bool[numSlots];

    // Initialize values with words and empty strings
    int wordIndex = 0;
    for (int i = 0; i < numSlots; i++) {
        if (wordIndex < size) {
            values[i] = words[wordIndex];
            values[i + 1] = words[wordIndex]; // Place each word in pairs
            i++; // Skip next iteration
        } else {
            values[i] = ""; // Fill the rest with empty strings
        }
        bShown[i] = false; // Initialize bShown
        wordIndex++;
    }
}

MemoryGame::~MemoryGame() {
    delete[] values;
    delete[] bShown;

    // Set values and bShown to nullptr after deletion
    values = nullptr;
    bShown = nullptr;
}

void MemoryGame::play() {
    randomize();
    int nonBlankCount = 0; // Track the number of non-blank cards shown
    while (nonBlankCount < numPairs * 2) {
        display(); // Show the current state of the game

        // Get user input for the first card
        int index1 = input();

        // Flip the first card
        bShown[index1] = true;
        display(); // Show the state after flipping the first card

        // Get user input for the second card
        int index2 = input();

        // Flip the second card
        bShown[index2] = true;
        display(); // Show the state after flipping the second card

        // Check if the flipped cards match
        if (values[index1] != values[index2]) {
            // If the cards don't match, hide them
            bShown[index1] = false;
            bShown[index2] = false;
        } else {
            // If the cards match, increment the non-blank count
            nonBlankCount += 2;
        }
    }

    cout << "Congratulations! You've matched all pairs." << endl;
}
void MemoryGame::display() const {
    //print labels
    cout << " ";
    for (int i = 0; i < numSlots; i++)
    cout << setw(3) << i << setw(3) << " ";
    //setw(3) before i means i occupies 3-character,
    //For example, if i has only two digits,
    //then pad a space to its left.

    cout << endl;
 

    // Print separated line
    printSeparatedLine(numSlots);

    // Print values
    cout << "|";
    for(int i = 0; i < numSlots; i++){
        if(bShown[i]){
            cout << setw(5) << values[i] << "|";
        }else{
            cout << "     |";
        }
    }
    cout << endl;

    // Print separated line
    printSeparatedLine(numSlots);
}
void MemoryGame::randomize()
{
    int size = 8;
    while (size > 1){
        int index = rand() % size;
        swap(values[index], values[size-1]);
        size--;
    }
}

int MemoryGame::input() const {
    int index;
    bool validInput = false;
    cout << "Enter an unflipped card in [0, " << numSlots - 1 << "]: ";
    cin >> index;
    while (!validInput) {

        if (index < 0 || index >= numSlots) {
            cout << "Input is not in [0, " << numSlots - 1 << "]. Re-enter: ";
            cin >> index;
        } else if (bShown[index]) {
            cout << "The card is flipped already. Re-enter: ";
            cin >> index;
        } else {
            validInput = true;
        }
    }
    return index;
}

void printSeparatedLine(int size) {
    cout << "+"; // The first +
    // Draw -----+ for (size) many times
    for (int i = 0; i < size; i++)
        cout << "-----+";

    cout << endl;
}

int main()
{
    MemoryGame game;
    game.play();

}
