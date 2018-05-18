#include <iostream>

#include "HelpFunctions.hpp"
#include "Spacer.hpp"

using namespace clever;
using namespace sf;



Spacer::Spacer(sf::Vector2f const &size): _size(size) {}

Spacer::~Spacer() {}



void Spacer::draw(
	sf::RenderTarget &target,
	sf::RenderStates states
) const {}



void Spacer::update(double time) {}



sf::Vector2f Spacer::getSize() const
{
	return _size;
}

bool Spacer::isResized() const
{
	return _isresized;
}

void Spacer::resetResized()
{
	_isresized = false;
	return;
}

void Spacer::setSize(sf::Vector2f const &newsize)
{
	if(_size.x != newsize.x || _size.y != newsize.y) {
		_size = newsize;
		_isresized = true;
	}
	return;
}



// end.
