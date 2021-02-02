#include "Game.h"

//sf::RenderWindow - 536
//sf::RectangleShape - 360
//sf::Color - 4
//sf::Texture - 40
//sf::String - 40
//sf::Font - 136
//sf::Text - 392
//Button - 384
//TextField - 576

int main()
{
	Game* TicTacToe{ new Game() };
	TicTacToe->MainLoop();
	return 0;
}