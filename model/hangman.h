///////////////////////////////////////////////////////////////////////
// File: Hangman.h
// Author: Robert Carll
// This assignment represents my own work and is in accordance with the College Academic Policy
// Copyright (c) 2015 All Right Reserved by Robert Carll
// Contributors:
// Description:
// Date: May 2016
// Revisions:
//////////////////////////////////////////////////////////////////////

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <QPushButton>

enum class Picture {ONE, // Enum for the picture of the hangman
                    TWO,
                    THREE,
                    FOUR,
                    FIVE,
                    SIX,
                    SEVEN
                  };

class Hangman
{
public:
    Hangman();
    ~Hangman();    

    void guess(char); // takes a char as a guess
    void newPhrase(); // generates a new phrase and resets values
    Picture show(); // shows the picture

    std::string workingPhrase() const; // uses the phrase to create a stringstream to show the underscores
    bool hasBeenGuessed(char) const; // checks to see if a letter has been guessed

    bool isWon() const; // checks if game was won
    bool isLost() const; // checks if game was lost
    std::string getPhrase(); // gets phrase to show answer on loss

private:
    std::vector<std::string> _words;
    std::string _phrase;
    std::set<char> _badGuesses;
    std::set<char> _goodGuesses;
    std::vector<QPushButton*> letters;
    static const std::vector<Picture> _pictureList;
};
