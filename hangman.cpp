#include "HangmanGame.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>

Word getRandomWord(const std::string& filePath) {
    std::ifstream fin(filePath);
    if (!fin.is_open()) {
        std::cerr << RED << "Error: Could not open words file." << RESET << std::endl;
        exit(1);
    }
    std::vector<std::string> words;
    std::string w;
    while (fin >> w) {
        words.push_back(w);
    }
    fin.close();
    if (words.empty()) {
        std::cerr << RED << "No words found in file." << RESET << std::endl;
        exit(1);
    }
    return Word(words[rand() % words.size()]);
}

int main(int argc, char* argv[]) {
    srand(time(nullptr)); // Seed random number generator

    if (argc < 2) {
        std::cout << "Usage: ./hangman <command> [args]" << std::endl;
        std::cout << "Commands:\n  start <words_file>" << std::endl;
        return 1;
    }

    std::string command = argv[1];

    if (command == "start") {
        if (argc < 3) {
            std::cerr << RED << "Missing words file argument." << RESET << std::endl;
            return 1;
        }
        std::string file = argv[2];
        Word w = getRandomWord(file);
        HangmanGame game(w);

        while (!game.isOver()) {
            game.printStatus();
            std::cout << GREEN << "Enter a letter: " << RESET;
            std::string input;
            std::cin >> input;
            if (input.size() != 1 || !isalpha(input[0])) {
                std::cout << RED << "Invalid input. Try a single letter." << RESET << std::endl;
                continue;
            }
            game.guess(input[0]);
        }

        game.printStatus();
        if (game.isWin()) std::cout << GREEN << "You won!" << RESET << std::endl;
        else std::cout << RED << "You lost! Word was: " << w.content << RESET << std::endl;

    } else {
        std::cerr << RED << "Unknown command." << RESET << std::endl;
    }

    return 0;
}