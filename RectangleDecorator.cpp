#include <iostream>

#include "HelpFunctions.hpp"
#include "RectangleDecorator.hpp"

using namespace clever;
using namespace sf;



RectangleDecorator::RectangleDecorator(
	Widget *widget,
	sf::RectangleShape *rect,
	sf::Vector2f const &borders
):
	_widget(widget), _rect(rect), _borders(borders) {
	updateSize();
}

RectangleDecorator::~RectangleDecorator()
{
	if(_rect)
		delete _rect;
	if(_widget)
		delete _widget;
	return;
}



void RectangleDecorator::update(double time)
{
	if(_widget) {
		_widget->update(time);
		if(_widget->isResized()) {
			updateSize();
			_widget->resetResized();
		}
	}
	return;
}

void RectangleDecorator::onClick(
	sf::Mouse::Button button,
	sf::Vector2f const &koor
)
{
	if(
		sf::FloatRect(_widget->getPosition(), _widget->getSize()).
		contains(koor.x, koor.y)
	) {
		_widget->onClick(
			button,
			koor-_widget->getPosition()
		);
	}
	return;
}



void RectangleDecorator::draw(
	sf::RenderTarget &target,
	sf::RenderStates states
) const
{
	if(_rect && _widget) {
		states.transform *= Transformable::getTransform();
		target.draw(*_rect, states);
		target.draw(*_widget, states);
	}
	return;
}



sf::Vector2f RectangleDecorator::getSize() const
{
	if(_rect && _widget)
		return _rect->getSize();
	else
		return {0, 0};
}

bool RectangleDecorator::isResized() const
{
	return _isresized;
}

void RectangleDecorator::resetResized()
{
	_isresized = false;
	return;
}

void RectangleDecorator::updateSize()
{
	if(_widget && _rect) {
		_rect->setPosition({0, 0});
		_rect->setSize(
			{_widget->getSize().x+2*_borders.x,
			_widget->getSize().y+2*_borders.y}
		);
		_widget->setPosition(_borders.x, _borders.y);
	}
	_isresized = true;
	return;
}



Widget *RectangleDecorator::getWidget() const
{
	return _widget;
}

Widget *RectangleDecorator::takeWidget()
{
	auto buf = _widget;
	_widget = nullptr;
	updateSize();
	return buf;
}

void RectangleDecorator::setWidget(Widget *newobject)
{
	if(_widget == newobject)
		return;
	if(_widget)
		delete _widget;
	_widget = newobject;
	updateSize();
	return;
}



sf::RectangleShape const *RectangleDecorator::getRectangle() const
{
	return _rect;
}

void RectangleDecorator::setRectangle(sf::RectangleShape *newrect)
{
	if(_rect == newrect)
		return;
	if(_rect)
		delete _rect;
	_rect = newrect;
	updateSize();
	return;
}



sf::Vector2f const &RectangleDecorator::getBorders() const
{
	return _borders;
}

void RectangleDecorator::setBorders(float newhborder, float newvborder)
{
	_borders = {newhborder, newvborder};
	updateSize();
	return;
}

void RectangleDecorator::setBorders(sf::Vector2f const &newborders)
{
	_borders = newborders;
	updateSize();
	return;
}



// end.
