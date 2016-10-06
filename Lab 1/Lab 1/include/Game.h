#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <time.h>
#include <iostream>

class Game
{
public:
	Game();
	Game(int maxGuessCount);

	int getGuessCount();
	void setMaxGuessCount(int maxGuess);

	int getMaxGuessCount();

	void incrementGuessCount();

	void initValue();

	int getValue();

	void playGame();

private:
	int m_iValue;
	int m_iGuessCount;
	int m_iMaxGuesses;

	bool seedInitialised = false;

	void initRandSeed();
	void printMenu(int currentGuess);
	int getUserInput();

};

Game::Game()
{
	m_iGuessCount = 0;
	m_iMaxGuesses = 5;
	m_iValue = 0;
}

Game::Game(int maxGuessCount) {
	m_iMaxGuesses = maxGuessCount;
	m_iGuessCount = 0;
	m_iValue = 0;
}

int Game::getGuessCount() {
	return m_iGuessCount;
}


void Game::setMaxGuessCount(int maxGuess) {
	m_iMaxGuesses = maxGuess;
}

inline int Game::getMaxGuessCount()
{
	return m_iMaxGuesses;
}

void Game::incrementGuessCount()
{
	++m_iGuessCount;
}

void Game::initValue()
{
	initRandSeed();
	m_iValue = rand() % 100 + 1;
}

int Game::getValue()
{
	return m_iValue;
}

void Game::playGame()
{
	int iCurrentGuess;
	bool bGameWon = false;
	printMenu(m_iGuessCount);
	while (m_iGuessCount < m_iMaxGuesses) {
		iCurrentGuess = getUserInput();
		incrementGuessCount();
		if (iCurrentGuess > 100 || iCurrentGuess < 1) {
			std::cout << "Please enter a number in the accepted range\n";
		}
		if (iCurrentGuess > m_iValue) {
			std::cout << "Too high\n";
		}
		else if (iCurrentGuess < m_iValue) {
			std::cout << "Too low\n";
		}
		else {
			std::cout << "You win!\n";
			bGameWon = true;
			break;
		}
		printMenu(m_iGuessCount);
	}
	if (!bGameWon) {
		std::cout << "You ran out of guesses! The number was " << getValue() <<"\n";
	}
}

void Game::printMenu(int currentGuess) {
	std::cout << "I'm thinking of a number between 1 and 100\n";
	std::cout << "You have " << (m_iMaxGuesses - m_iGuessCount) << " guesses remaining\n";
}

int Game::getUserInput() {
	std::cout << "Please enter your guess: \n";
	int currentGuess;
	std::cin >> currentGuess;
	return currentGuess;
}

void Game::initRandSeed() {
	if (!seedInitialised) {
		srand(time(NULL));
		seedInitialised = true;
	}
}


#endif