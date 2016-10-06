#include "Game.h"
#include <iostream>

using namespace std;

void main() {
	Game game(5);
	game.initValue();
	game.playGame();

	system("pause");
}