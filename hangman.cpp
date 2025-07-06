// Hangman Game - Command Line Based
// Author: Fodor Robert Mihai
// Grading: 40 points criteria implementation

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

// ANSI color codes
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

class Word {
public:
    string content;
    Word(string c) : content(move(c)) {}
};

class HangmanGame {
private:
    Word word;
    set<char> guessed;
    int maxTries;
    int incorrect;

public:
    HangmanGame(const Word& w, int max_tries = 6) : word(w), maxTries(max_tries), incorrect(0) {}

    bool guess(char c) {
        if (guessed.count(c)) return false;
        guessed.insert(c);
        if (word.content.find(c) == string::npos) {
            incorrect++;
            return false;
        }
        return true;
    }

    string maskedWord() const {
        string masked;
        for (char ch : word.content) {
            if (guessed.count(ch)) masked += ch;
            else masked += '_';
        }
        return masked;
    }

    bool isOver() const {
        return incorrect >= maxTries || maskedWord() == word.content;
    }

    bool isWin() const {
        return maskedWord() == word.content;
    }

    void printStatus() {
        cout << YELLOW << "Word: " << maskedWord() << RESET << endl;
        cout << RED << "Incorrect tries: " << incorrect << "/" << maxTries << RESET << endl;
    }
};

Word getRandomWord(const string& filePath) {
    ifstream fin(filePath);
    if (!fin.is_open()) {
        cerr << RED << "Error: Could not open words file." << RESET << endl;
        exit(1);
    }
    vector<string> words;
    string w;
    while (fin >> w) {
        words.push_back(w);
    }
    fin.close();
    if (words.empty()) {
        cerr << RED << "No words found in file." << RESET << endl;
        exit(1);
    }
    return Word(words[rand() % words.size()]);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./hangman <command> [args]" << endl;
        cout << "Commands:\n  start <words_file>" << endl;
        return 1;
    }

    string command = argv[1];

    if (command == "start") {
        if (argc < 3) {
            cerr << RED << "Missing words file argument." << RESET << endl;
            return 1;
        }
        string file = argv[2];
        Word w = getRandomWord(file);
        HangmanGame game(w);

        while (!game.isOver()) {
            game.printStatus();
            cout << GREEN << "Enter a letter: " << RESET;
            string input;
            cin >> input;
            if (input.size() != 1 || !isalpha(input[0])) {
                cout << RED << "Invalid input. Try a single letter." << RESET << endl;
                continue;
            }
            game.guess(tolower(input[0]));
        }

        game.printStatus();
        if (game.isWin()) cout << GREEN << "You won!" << RESET << endl;
        else cout << RED << "You lost! Word was: " << w.content << RESET << endl;

    } else {
        cerr << RED << "Unknown command." << RESET << endl;
    }

    return 0;
}
