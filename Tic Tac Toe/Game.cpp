#include "Game.h"
#include <iostream>

Game::Game()
	: CurrentPlayer(), GameState(GAMESTATE::NOTSTARTED), Window(sf::VideoMode{ 1000, 600 }, L"Kó³ko i Krzy¿yk", sf::Style::Close)
{
	Cross.loadFromFile("Cross.jpg");
	Circle.loadFromFile("Circle.jpg");
	MainFont.loadFromFile("LifeSavers-Bold.ttf");
}

void Game::MainLoop()
{
	srand(static_cast<unsigned int>(time(NULL)));

	sf::Event Event;

	CreateObjects();

	while (Window.isOpen())
	{
		while (Window.pollEvent(Event))
		{
			switch (Event.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;
			}
		}

		UpdateObjects();

		DrawObjects();
	}
}

void Game::StartGame()
{
	GameState = { GAMESTATE::MOVE };
	if (rand() % 2 == 1)
	{
		CurrentPlayer = { SIGN::CIRCLE };
		GameStateTextField->SetString(L"  Aktualny gracz: O");
	}
	else
	{
		CurrentPlayer = { SIGN::CROSS };
		GameStateTextField->SetString(L"  Aktualny gracz: X");
	}
}

void Game::CreateObjects()
{
	for (int i = 0; i < 9; ++i)
	{
		FieldButtons.push_back(new Button(static_cast<float>(100 + i % 3 * 140), static_cast<float>(100 + i / 3 * 140), 120, 120,
			i + 1, sf::Color(206, 245, 237), sf::Color(73, 204, 173), sf::Color(206, 245, 237)));
	}

	FieldRectangle->setFillColor(sf::Color(5, 117, 96));
	FieldRectangle->setPosition(sf::Vector2f{ 80, 80 });
	FieldRectangle->setSize(sf::Vector2f{ 440, 440 });
}

void Game::UpdateObjects()
{
	switch (GameState)
	{
	case GAMESTATE::NOTSTARTED:
		if (OneVsOneButton->Update(Window) == BUTTONSTATE::ACTIVE)
		{
			sf::sleep(sf::milliseconds(200));
			StartGame();
		}

		if (ComputerVsOneButton->Update(Window) == BUTTONSTATE::ACTIVE)
		{
			GameState = { GAMESTATE::SELECTION };
		}

		if (MenuExitButton->Update(Window) == BUTTONSTATE::ACTIVE)
		{
			Window.close();
		}

		break;

	case GAMESTATE::DRAW:

	case GAMESTATE::WIN:
		if (ExitButton->Update(Window) == BUTTONSTATE::ACTIVE)
		{
			Window.close();
		}

		if (PlayAgainButton->Update(Window) == BUTTONSTATE::ACTIVE)
		{
			for (Button* Object : FieldButtons)
			{
				Object->SetTexture(NULL);

				for (int i = 0; i < 3; ++i)
				{
					for (int j = 0; j < 3; ++j)
					{
						Matrix[i][j] = FIELD::EMPTY;
					}
				}
			}

			StartGame();
		}

	case GAMESTATE::MOVE:
		if (BackButton->Update(Window) == BUTTONSTATE::ACTIVE)
		{
			for (Button* Object : FieldButtons)
			{
				Object->SetTexture(NULL);

				for (int i = 0; i < 3; ++i)
				{
					for (int j = 0; j < 3; ++j)
					{
						Matrix[i][j] = FIELD::EMPTY;
					}
				}
			}

			GameState = { GAMESTATE::NOTSTARTED };
		}

		for (Button* Object : FieldButtons)
		{
			if (Matrix[(Object->GetNumber() - 1) % 3][(Object->GetNumber() - 1) / 3] == FIELD::EMPTY && GameState == GAMESTATE::MOVE)
			{
				if (Object->Update(Window) == BUTTONSTATE::ACTIVE)
				{
					Move(Object->GetNumber());
				}
			}
		}

		break;

	case GAMESTATE::SELECTION:
		if (BackButton->Update(Window) == BUTTONSTATE::ACTIVE)
		{
			GameState = { GAMESTATE::NOTSTARTED };
		}

		if (EasyButton->Update(Window) == BUTTONSTATE::ACTIVE)
		{

		}

		if (MediumButton->Update(Window) == BUTTONSTATE::ACTIVE)
		{

		}

		if (HardButton->Update(Window) == BUTTONSTATE::ACTIVE)
		{

		}

		if (ImpossibleButton->Update(Window) == BUTTONSTATE::ACTIVE)
		{

		}

		break;

	}
}

void Game::DrawObjects()
{
	Window.clear(sf::Color(73, 204, 173));

	TicTacToeTextField->Draw(Window);

	switch (GameState)
	{
	case GAMESTATE::NOTSTARTED:
		GameModeTextField->Draw(Window);

		OneVsOneButton->Draw(Window);
		OneVsOneTextField->Draw(Window);

		ComputerVsOneButton->Draw(Window);
		OneVsComputerTextField->Draw(Window);

		MenuExitButton->Draw(Window);
		MenuExitTextField->Draw(Window);

		break;

	case GAMESTATE::DRAW:

	case GAMESTATE::WIN:
		PlayAgainButton->Draw(Window);
		ExitButton->Draw(Window);

		PlayAgainTextField->Draw(Window);
		ExitTextField->Draw(Window);

	case GAMESTATE::MOVE:
		BackButton->Draw(Window);
		BackTextField->Draw(Window);

		GameStateTextField->Draw(Window);

		Window.draw(*FieldRectangle);

		for (Button* Object : FieldButtons)
		{
			Object->Draw(Window);
		}

		break;

	case GAMESTATE::SELECTION:
		BackButton->Draw(Window);
		BackTextField->Draw(Window);

		EasyButton->Draw(Window);
		EasyTextField->Draw(Window);

		MediumButton->Draw(Window);
		MediumTextField->Draw(Window);

		HardButton->Draw(Window);
		HardTextField->Draw(Window);

		ImpossibleButton->Draw(Window);
		ImpossibleTextField->Draw(Window);
	}

	Window.display();
}

void Game::Move(int NumberOfField)
{
	int x{ (NumberOfField - 1) % 3 };
	int y{ (NumberOfField - 1) / 3 };

	if (Matrix[x][y] == FIELD::EMPTY)
	{
		if (CurrentPlayer == SIGN::CIRCLE)
		{
			Matrix[x][y] = { FIELD::CIRCLE };
			FieldButtons[static_cast<long long>(NumberOfField) - 1]->SetTexture(&Circle);
		}
		else
		{
			Matrix[x][y] = { FIELD::CROSS };
			FieldButtons[static_cast<long long>(NumberOfField) - 1]->SetTexture(&Cross);
		}
	}
	else
	{
		return;
	}

	FIELD CompatibleField;

	int AmountOfCompatibleFields;

	for (int i = 0; i < 8; ++i)
	{
		CompatibleField = { FIELD::EMPTY };
		AmountOfCompatibleFields = { 0 };

		for (int j = 0; j < 3; ++j)
		{
			if (Matrix[Lines[i][j][0]][Lines[i][j][1]] != CompatibleField)
			{
				CompatibleField = { Matrix[Lines[i][j][0]][Lines[i][j][1]] };
				AmountOfCompatibleFields = { 1 };
			}
			else
			{
				++AmountOfCompatibleFields;
			}
		}

		if (AmountOfCompatibleFields == 3 && CompatibleField != FIELD::EMPTY)
		{
			GameState = GAMESTATE::WIN;

			if (CurrentPlayer == SIGN::CROSS)
			{
				GameStateTextField->SetString(L"    Wygra³ gracz: X");
			}
			else
			{
				GameStateTextField->SetString(L"    Wygra³ gracz: O");
			}

			return;
		}
	}

	int AmountOfFilledFields = { 0 };

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (Matrix[i][j] != FIELD::EMPTY)
			{
				++AmountOfFilledFields;
			}
		}
	}

	if (AmountOfFilledFields == 9)
	{
		GameState = GAMESTATE::DRAW;
		
		GameStateTextField->SetString(L"             Remis");

		return;
	}

	if (CurrentPlayer == SIGN::CIRCLE)
	{
		CurrentPlayer = { SIGN::CROSS };
		GameStateTextField->SetString(L"  Aktualny gracz: X");
	}
	else
	{
		CurrentPlayer = { SIGN::CIRCLE };
		GameStateTextField->SetString(L"  Aktualny gracz: O");
	}
}