#ifndef HANGMANGAME_H
#define HANGMANGAME_H

#include "Word.h"
#include <set>
#include <string>

// ANSI color codes
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RESET = "\033[0m";

class HangmanGame {
private:
    Word word;
    std::set<char> guessed;
    int maxTries;
    int incorrect;

public:
    HangmanGame(const Word& w, int max_tries = 6);
    bool guess(char c);
    std::string maskedWord() const;
    bool isOver() const;
    bool isWin() const;
    void printStatus();
};

#endif // HANGMANGAME_H