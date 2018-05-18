#include <iostream>
#include "HelpFunctions.hpp"
#include "Layout.hpp"

using namespace clever;



Layout::Layout(
	Orientation orientation,
	std::vector<Widget*> const &elements,
	sf::Vector2f const &borders
): _orientation(orientation), _elements(elements), _borders(borders) 
{
	updateSize();
	return;
}

Layout::~Layout()
{
	for(auto i : _elements)
		delete i;
}



void Layout::update(double time)
{
	for(auto i : _elements)
		i->update(time);
	for(auto i : _elements)
		if(i->isResized()) {
			updateSize();
			for(auto i : _elements)
				i->resetResized();
			break;
		}
	return;
}

void Layout::onClick(
	sf::Mouse::Button button,
	sf::Vector2f const &koor
)
{
	std::cout << "Layout::onClick" << koor << std::endl;
	for(auto i : _elements) {
		std::cout << "Assert: " <<
			sf::FloatRect(i->getPosition(), i->getSize()) <<
			std::endl;
		if(
			sf::FloatRect(i->getPosition(), i->getSize()).
			contains(koor.x, koor.y)
		) {
			std::cout << "Find element" << std::endl;
			i->onClick(
				button, 
				koor-i->getPosition()
			);
			break;
		}
	}
	return;
}



void Layout::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= sf::Transformable::getTransform();
	for(auto i : _elements)
		target.draw(*i, states);
	return;

}



sf::Vector2f Layout::getSize() const
{
	return _size;
}

bool Layout::isResized() const
{
	return _isresized;
}

void Layout::resetResized()
{
	_isresized = false;
	return;
}

void Layout::updateSize()
{
	float last;
	switch(_orientation) {
	case horizontal:
		if(_elements.empty()) {
			_size.x = 0.0f;
			_size.y = 0.0f;
		}
		else {
			_size.y = _elements.front()->getSize().y;
			for(auto i : _elements) {
				if(i->getSize().y > _size.y)
					_size.y = i->getSize().y;
			}
			_size.y += 2*_borders.y;

		
			last = _borders.x;
			switch(_alignement) {
			case right: case up:
				for(auto i : _elements) {
					i->setPosition(last, _borders.y);
					last += i->getSize().x + _borders.x;
				}
				_size.x = last;
				break;
			case left: case down:
				for(auto i : _elements) {
					i->setPosition(
						last, _size.y-
						(_borders.y+i->getSize().y)
					);
					last += i->getSize().x + _borders.x;
				}
				_size.x = last;
				break;
			case center:
				for(auto i : _elements) {
					i->setPosition(
						last,
						(_size.y - i->getSize().y)/2
					);
					last += i->getSize().x + _borders.x;
				}
				_size.x = last;
				break;
			default:
				throw "Undefined Alignement";
			}
		}
		break;
	case vertical:
		if(_elements.empty()) {
			_size.x = 0.0f;
			_size.y = 0.0f;
		}
		else {
			_size.x = _elements.front()->getSize().x;
			for(auto i : _elements) {
				if(i->getSize().x > _size.x)
					_size.x = i->getSize().x;
			}
			_size.x += 2*_borders.x;

		
			last = _borders.y;
			switch(_alignement) {
			case right: case up:
				for(auto i : _elements) {
					i->setPosition(_borders.y, last);
					last += i->getSize().y + _borders.y;
				}
				_size.y = last;
				break;
			case left: case down:
				for(auto i : _elements) {
					i->setPosition(
						_size.x-(_borders.x +
						i->getSize().x), last
					);
					last += i->getSize().y + _borders.y;
				}
				_size.y = last;
				break;
			case center:
				for(auto i : _elements) {
					i->setPosition(
						(_size.x-i->getSize().x)/2,
						last
					);
					last += i->getSize().y + _borders.y;
				}
				_size.y = last;
				break;
			default:
				throw "Undefined Alignement";
			}
		}
		break;
	default:
		throw "Undefined orientation";
	}

	_isresized = true;

	return;
}



void Layout::add(Widget *widget)
{
	_elements.push_back(widget);
	return;
}

void Layout::insertBefore(Widget const *before, Widget *toinsert)
{
	for(auto b = _elements.begin(), e = _elements.end(); b != e; ++b) {
		if(*b == before) {
			_elements.insert(b, toinsert);
			updateSize();
			return;
		}
	}
	_elements.push_back(toinsert);
	updateSize();
	return;
}

void Layout::remove(Widget const *widget)
{
	for(auto b = _elements.begin(), e = _elements.end(); b != e; ++b) {
		if(*b == widget) {
			delete *b;
			_elements.erase(b);
			break;
		}
	}
	updateSize();
	return;
}

void Layout::removeAll()
{
	for(auto i : _elements)
		delete i;
	_elements.clear();
	updateSize();
	return;
}

void Layout::release(Widget const *widget)
{
	for(auto b = _elements.begin(), e = _elements.end(); b != e; ++b) {
		if(*b == widget) {
			_elements.erase(b);
			break;
		}
	}
	updateSize();
	return;
}

void Layout::releaseAll()
{
	_elements.clear();
	updateSize();
	return;
}



std::vector<Widget*> const &Layout::getElements() const
{
	return _elements;
}



sf::Vector2f const &Layout::getBorders() const
{
	return _borders;
}

void Layout::setBorders(sf::Vector2f const &newborders)
{
	_borders = newborders;
	updateSize();
	return;
}



Layout::Orientation Layout::getOrientation() const
{
	return _orientation;
}

void Layout::setOrientation(Orientation neworientation)
{
	_orientation = neworientation;
	updateSize();
	return;
}



Layout::Alignement Layout::getAlignement() const
{
	return _alignement;
}

void Layout::setAlignement(Layout::Alignement newalignement)
{
	_alignement = newalignement;
	updateSize();
	return;
}



// end.
