#include "TextField.h"

TextField::TextField(sf::String _String, float x, float y, int _CharacterSize, sf::Font* Font, sf::Color _TextColor)
	: String(_String), CharacterSize(_CharacterSize), TextColor(_TextColor)
{
	Text.setString(String);
	Text.setPosition(x, y);
	Text.setFont(*Font);
	Text.setCharacterSize(CharacterSize);
	Text.setFillColor(TextColor);
}

TextField::TextField(float x, float y, int _CharacterSize, sf::Font* Font, sf::Color _TextColor)
	: CharacterSize(_CharacterSize), TextColor(_TextColor)
{
	Text.setString(String);
	Text.setPosition(x, y);
	Text.setFont(*Font);
	Text.setCharacterSize(CharacterSize);
	Text.setFillColor(TextColor);
}

void TextField::Draw(sf::RenderWindow& Window)
{
	Window.draw(Text);
}

void TextField::SetString(sf::String _String)
{
	String = { _String };
	Text.setString(String);
}