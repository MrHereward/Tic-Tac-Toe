#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

enum class BUTTONSTATE : char
{
	IDLE,
	HOVER,
	ACTIVE
};

class Button
{
private:
	sf::RectangleShape Field;

	sf::String ButtonString;

	sf::Color IdleColor;
	sf::Color HoverColor;
	sf::Color ActiveColor;

	int Number;

	BUTTONSTATE ButtonState;

public:
	Button(float x, float y, float Width, float Height, int _Number, sf::Color _IdleColor, sf::Color _HoverColor, sf::Color _ActiveColor);

	BUTTONSTATE Update(sf::RenderWindow& Window);

	void Draw(sf::RenderWindow& Window);

	int GetNumber();

	void SetTexture(sf::Texture* Texture);
};