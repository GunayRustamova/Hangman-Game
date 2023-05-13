#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

const int MAX_TRIES = 6;

struct Node {
    char letter;
    bool guessed;
};

struct LinkedList {
    Node* nodes;
    int size;
};

void initializeLinkedList(LinkedList& list, const string& word) {
    list.size = word.length();
    list.nodes = new Node[list.size];

    for (int i = 0; i < list.size; ++i) {
        list.nodes[i].letter = word[i];
        list.nodes[i].guessed = false;
    }
}

void deleteLinkedList(LinkedList& list) {
    delete[] list.nodes;
}

bool isGameWon(const LinkedList& list) {
    for (int i = 0; i < list.size; ++i) {
        if (!list.nodes[i].guessed) {
            return false;
        }
    }
    return true;
}

void displayWord(const LinkedList& list) {
    for (int i = 0; i < list.size; ++i) {
        if (list.nodes[i].guessed) {
            cout << list.nodes[i].letter << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

bool isLetterInWord(const LinkedList& list, char letter) {
    for (int i = 0; i < list.size; ++i) {
        if (list.nodes[i].letter == letter) {
            return true;
        }
    }
    return false;
}

void updateGuessedLetters(LinkedList& list, char letter) {
    for (int i = 0; i < list.size; ++i) {
        if (list.nodes[i].letter == letter) {
            list.nodes[i].guessed = true;
        }
    }
}

char getGuess() {
    char guess;
    cout << "Enter a letter: ";
    cin >> guess;
    guess = tolower(guess);  // Convert guess to lowercase
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer
    return guess;
}

void drawRodman() {
    cout << "   ____" << endl;
    cout << "  |    |" << endl;
    cout << "  |    O" << endl;
    cout << "  |   /|\\" << endl;
    cout << "  |   / \\      HANGMAN" << endl;
    cout << " _|_              GAME " << endl;
    cout << "|   |______" << endl;
    cout << "|          |" << endl;
    cout << "|__________|" << endl;
}

int main() {
    char again;

    drawRodman();

    srand(static_cast<unsigned int>(time(0)));

    const string words[] = {"hangman", "data", "structure","apple", "banana", "orange","computer", "programming", "pear", "grape", "rain", "key", "angel", "ghost", "robot", "coin", "lamp"};
    const int numWords = sizeof(words) / sizeof(words[0]);
    string word = words[rand() % numWords];

    LinkedList wordList;
    initializeLinkedList(wordList, word);

    int tries = 0;
    char guess;
    while (tries < MAX_TRIES) {
        cout << "\nYou have " << (MAX_TRIES - tries) << " wrong guesses left"<< endl;
        displayWord(wordList);

        guess = getGuess();
        if (isLetterInWord(wordList, guess)) {
            updateGuessedLetters(wordList, guess);
            if (isGameWon(wordList)) {
                cout << "\nCongratulations! You guessed the word!" << endl;
                break;
            }
        } else {
            ++tries;
            cout << "Incorrect guess!" << endl;
        }
    }

    if (tries == MAX_TRIES) {
        cout << "\nSorry, you lost. The word was: " << word << endl;
    }

    deleteLinkedList(wordList);

    cout<<"\nDo you want to play the game again?(y/n)"<<endl;
    cin>>again;
    if(again=='y' || again=='Y'){
        return main();
    }

    return 0;
}