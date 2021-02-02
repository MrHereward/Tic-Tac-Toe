#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class TextField
{
private:
	sf::Text Text;

	sf::Font Font;

	sf::String String;

	sf::Color TextColor;

	int CharacterSize;

public:
	TextField(sf::String _String, float x, float y, int _CharacterSize, sf::Font* Font, sf::Color _TextColor);

	TextField(float x, float y, int _CharacterSize, sf::Font* Font, sf::Color _TextColor);

	void Draw(sf::RenderWindow& Window);

	void SetString(sf::String _String);

};