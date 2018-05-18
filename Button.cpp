#include "Button.hpp"

using namespace clever;



Button::Button(
	Widget *widget,
	sf::RectangleShape *rect,
	sf::Vector2f const &borders
): RectangleDecorator(widget, rect, borders) {}

Button::~Button() {}



void Button::onClick(
	sf::Mouse::Button button,
	sf::Vector2f const &
)
{
	if(_onclickfun)
		_onclickfun(button);
	return;
}



std::function<void(sf::Mouse::Button)> const &
Button::getOnClickFunction() const
{
	return _onclickfun;
}

void Button::setOnClickFunction(
	std::function<void(sf::Mouse::Button)> const &newfun
)
{
	_onclickfun = newfun;
	return;
}



// end.
