#include "HangmanGame.h"
#include <cctype>
#include <iostream>

HangmanGame::HangmanGame(const Word& w, int max_tries) 
    : word(w), maxTries(max_tries), incorrect(0) {}

bool HangmanGame::guess(char c) {
    c = static_cast<char>(tolower(static_cast<unsigned char>(c)));  // Fixed line
    if (guessed.count(c)) return false;
    guessed.insert(c);
    if (word.content.find(c) == std::string::npos) {
        incorrect++;
        return false;
    }
    return true;
}

std::string HangmanGame::maskedWord() const {
    std::string masked;
    for (char ch : word.content) {
        char lower_ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        if (guessed.count(lower_ch)) masked += ch;
        else masked += '_';
    }
    return masked;
}

bool HangmanGame::isOver() const {
    return incorrect >= maxTries || maskedWord() == word.content;
}

bool HangmanGame::isWin() const {
    return maskedWord() == word.content;
}

void HangmanGame::printStatus() {
    std::cout << YELLOW << "Word: " << maskedWord() << RESET << std::endl;
    std::cout << RED << "Incorrect tries: " << incorrect << "/" << maxTries << RESET << std::endl;
}