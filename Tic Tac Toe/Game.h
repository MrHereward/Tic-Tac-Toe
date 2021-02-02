#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "Button.h"
#include "TextField.h"

enum class SIGN : char
{
	CIRCLE = 'O',
	CROSS = 'X',
	last
};

enum class FIELD : char
{
	EMPTY,
	CIRCLE = 'O',
	CROSS = 'X'
};

enum class GAMESTATE : char
{
	NOTSTARTED,
	SELECTION,
	MOVE,
	WIN,
	DRAW
};

enum class DIFFICULTYLEVEL : char
{
	EASY,
	MEDIUM,
	HARD,
	IMPOSIBLE
};

class Game
{
private:
	TextField* PlayAgainTextField{ new TextField(L"Zagraj ponownie", 610, 150, 40, &MainFont, sf::Color(206, 245, 237)) };

	TextField* ExitTextField{ new TextField(L"Wyjdü", 690, 400, 40, &MainFont, sf::Color(206, 245, 237)) };

	TextField* BackTextField{ new TextField(L"PowrÛt", 6, 8, 20, &MainFont, sf::Color(5, 117, 96)) };

	TextField* TicTacToeTextField{ new TextField(L"K”£KO I KRZYØYK", 220, 10, 60, &MainFont, sf::Color(5, 117, 96)) };

	TextField* GameStateTextField{ new TextField(620, 280, 30, &MainFont, sf::Color(206, 245, 237)) };

	TextField* GameModeTextField{ new TextField(L"Wybierz tryb gry:", 335, 150, 40, &MainFont, sf::Color(206, 245, 237)) };

	TextField* OneVsOneTextField{ new TextField(L"Gracz vs Gracz", 405, 250, 30, &MainFont, sf::Color(206, 245, 237)) };

	TextField* OneVsComputerTextField{ new TextField(L"Gracz vs Komputer", 370, 350, 30, &MainFont, sf::Color(206, 245, 237)) };

	TextField* MenuExitTextField{ new TextField(L"Wyjdü", 455, 450, 30, &MainFont, sf::Color(206, 245, 237)) };

	TextField* EasyTextField{ new TextField(L"£atwy", 455, 145, 30, &MainFont, sf::Color(206, 245, 237)) };

	TextField* MediumTextField{ new TextField(L"åredni", 455, 245, 30, &MainFont, sf::Color(206, 245, 237)) };

	TextField* HardTextField{ new TextField(L"Trudny", 445, 345, 30, &MainFont, sf::Color(206, 245, 237)) };

	TextField* ImpossibleTextField{ new TextField(L"Niemoøliwy", 415, 445, 30, &MainFont, sf::Color(206, 245, 237)) };

	sf::RenderWindow Window;

	std::vector<Button*> FieldButtons;

	Button* PlayAgainButton{ new Button(600, 135, 320, 80, 10, sf::Color(73, 204, 173, 1), sf::Color(5, 117, 96), sf::Color(73, 204, 173, 1)) };

	Button* ExitButton{ new Button(600, 385, 320, 80, 11, sf::Color(73, 204, 173, 1), sf::Color(5, 117, 96), sf::Color(73, 204, 173, 1)) };

	Button* BackButton{ new Button(0, 0, 80, 40, 12, sf::Color(73, 204, 173, 1), sf::Color(206, 245, 237), sf::Color(73, 204, 173, 1)) };

	Button* OneVsOneButton{ new Button(350, 245, 300, 50, 13, sf::Color(73, 204, 173, 1), sf::Color(5, 117, 96), sf::Color(73, 204, 173, 1)) };

	Button* ComputerVsOneButton{ new Button(350, 345, 300, 50, 14, sf::Color(73, 204, 173, 1), sf::Color(5, 117, 96), sf::Color(73, 204, 173, 1)) };

	Button* MenuExitButton{ new Button(350, 445, 300, 50, 15, sf::Color(73, 204, 173, 1), sf::Color(5, 117, 96), sf::Color(73, 204, 173, 1)) };

	Button* EasyButton{ new Button(350, 140, 300, 50, 16, sf::Color(73, 204, 173, 1), sf::Color(5, 117, 96), sf::Color(73, 204, 173, 1)) };

	Button* MediumButton{ new Button(350, 240, 300, 50, 17, sf::Color(73, 204, 173, 1), sf::Color(5, 117, 96), sf::Color(73, 204, 173, 1)) };

	Button* HardButton{ new Button(350, 340, 300, 50, 18, sf::Color(73, 204, 173, 1), sf::Color(5, 117, 96), sf::Color(73, 204, 173, 1)) };

	Button* ImpossibleButton{ new Button(350, 440, 300, 50, 19, sf::Color(73, 204, 173, 1), sf::Color(5, 117, 96), sf::Color(73, 204, 173, 1)) };

	sf::RectangleShape* FieldRectangle{ new sf::RectangleShape() };

	sf::Font MainFont;

	sf::Texture Cross;
	sf::Texture Circle;

	sf::String GameStateString;

	const int Lines[8][3][2] =
	{
		{ { 0,0 }, { 0,1 }, { 0,2 } },
		{ { 1,0 }, { 1,1 }, { 1,2 } },
		{ { 2,0 }, { 2,1 }, { 2,2 } },
		{ { 0,0 }, { 1,0 }, { 2,0 } },
		{ { 0,1 }, { 1,1 }, { 2,1 } },
		{ { 0,2 }, { 1,2 }, { 2,2 } },
		{ { 0,0 }, { 1,1 }, { 2,2 } },
		{ { 2,0 }, { 1,1 }, { 0,2 } }
	};

	SIGN CurrentPlayer;

	GAMESTATE GameState;

	FIELD Matrix[3][3] =
	{
		{ FIELD::EMPTY, FIELD::EMPTY, FIELD::EMPTY },
		{ FIELD::EMPTY, FIELD::EMPTY, FIELD::EMPTY },
		{ FIELD::EMPTY, FIELD::EMPTY, FIELD::EMPTY }
	};

public:
	Game();

	void MainLoop();

	void StartGame();

	void CreateObjects();

	void UpdateObjects();

	void DrawObjects();

	void Move(int NumberOfField);
};