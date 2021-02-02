#include "Button.h"

Button::Button(float x, float y, float Width, float Height, int _Number, sf::Color _IdleColor, sf::Color _HoverColor, sf::Color _ActiveColor)
	: Number(_Number), ButtonState(BUTTONSTATE::IDLE), IdleColor(_IdleColor), HoverColor(_HoverColor), ActiveColor(_ActiveColor)
{
	Field.setPosition(sf::Vector2f(x, y));
	Field.setSize(sf::Vector2f(Width, Height));
	Field.setFillColor(IdleColor);
}

BUTTONSTATE Button::Update(sf::RenderWindow& Window)
{
	ButtonState = { BUTTONSTATE::IDLE };

	if (sf::Mouse::getPosition(Window).x < Field.getPosition().x + Field.getLocalBounds().width &&
		sf::Mouse::getPosition(Window).x > Field.getPosition().x &&
		sf::Mouse::getPosition(Window).y < Field.getPosition().y + Field.getLocalBounds().height &&
		sf::Mouse::getPosition(Window).y > Field.getPosition().y)
	{
		ButtonState = { BUTTONSTATE::HOVER };

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			ButtonState = { BUTTONSTATE::ACTIVE };
		}
	}

	switch (ButtonState)
	{
	case BUTTONSTATE::IDLE:
		Field.setFillColor(IdleColor);
		return BUTTONSTATE::IDLE;
	case BUTTONSTATE::HOVER:
		Field.setFillColor(HoverColor);
		return BUTTONSTATE::HOVER;
	case BUTTONSTATE::ACTIVE:
		Field.setFillColor(ActiveColor);
		return BUTTONSTATE::ACTIVE;
	}
}

void Button::Draw(sf::RenderWindow& Window)
{
	Window.draw(Field);
}

int Button::GetNumber()
{
	return Number;
}

void Button::SetTexture(sf::Texture* Texture)
{
	Field.setTexture(Texture);
}