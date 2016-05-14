///////////////////////////////////////////////////////////////////////
// File: Hangman.cpp
// Author: Robert Carll
// This assignment represents my own work and is in accordance with the College Academic Policy
// Copyright (c) 2015 All Right Reserved by Robert Carll
// Contributors:
// Description:
// Date: May 2016
// Revisions:
//////////////////////////////////////////////////////////////////////


#include "Hangman.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>

Picture Hangman::show() // shows the picture based on how many wrong guesses were made
{

    switch (_badGuesses.size())
    {
    case 0:\
        return Picture::ONE;
        break;
    case 1:
        return Picture::TWO;
        break;
    case 2:
        return Picture::THREE;
        break;
    case 3:
        return Picture::FOUR;
        break;
    case 4:
        return Picture::FIVE;
        break;
    case 5:
        return Picture::SIX;
        break;
    default:
        return Picture::SEVEN;
        break;
    }
}

void Hangman::guess(char c) // Takes a letter as a guess and inserts it into the proper set
{
    if(isWon() || isLost())
        return;

    if (std::string::npos == _phrase.find(c))
        _badGuesses.insert(c);
    else
        _goodGuesses.insert(c);

}

void Hangman::newPhrase() // clears previous guesses and gets new phrase randomly from vector
{
    _goodGuesses.clear();
    _badGuesses.clear();
    srand(unsigned(time(0)));
    _phrase = _words[rand() % _words.size()];
    _goodGuesses.insert(' ');
}

std::string Hangman::workingPhrase() const // Shows the phrase as underscores
{
    std::stringstream ss;

    for (char c : _phrase)
    {
        if (_goodGuesses.find(c) != _goodGuesses.end())
            ss << c << " ";
        else
            ss << "_ ";
    }

    return ss.str();
}

bool Hangman::hasBeenGuessed(char c) const // checks to see if a char has already been guessed
{
    if (_goodGuesses.find(c) != _goodGuesses.end() || _badGuesses.find(c) != _badGuesses.end())
        return true;
    else
        return false;
}

bool Hangman::isWon() const // Checks to see if game has been won
{

    for (char c : _phrase)
    {
        if (_goodGuesses.find(c) == _goodGuesses.end())
            return false;
    }
    return true;
}

bool Hangman::isLost() const // checks to see if game has been lost
{
    if (_badGuesses.size() == 6)
        return true;
    else
        return false;
}

Hangman::Hangman()
{
    std::ifstream ifile;
    ifile.open("C:\\hangman.txt");

    if (ifile.fail()) // if file cannot be read closes program
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        while (!ifile.eof()) // reads the file and populates the vector with each word
        {
            getline(ifile, _phrase);
            _words.push_back(_phrase);
        }
    }
    ifile.close();
}

std::string Hangman::getPhrase(){ // returns the phrase (used if the character losses)
    return _phrase;
}

Hangman::~Hangman()
{
}

