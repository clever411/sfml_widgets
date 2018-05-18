#include "HelpFunctions.hpp"
#include "StatusBar.hpp"

using namespace clever;



StatusBar::StatusBar(
	sf::Text *text,
	clever::ChangingObject<std::string> const *status,
	sf::Vector2f const &space
): _text(text), _status(status), _space(space)
{
	if(_status && _text)
		_text->setString(_status->get());
}

StatusBar::~StatusBar()
{
	if(_text)
		delete _text;
	return;
}



void StatusBar::update(double time)
{
	if(_status && _text)
		if(_status->isChanged()) {
			_text->setString(_status->get());
			if(_align != left)
				_adjustPosition();
			_status->reset();
		}
	return;
}



void StatusBar::draw(
	sf::RenderTarget &target,
	sf::RenderStates states
) const
{
	if(_text) {
		states.transform *= Transformable::getTransform();
		target.draw(*_text, states);
	}
	return;
}



sf::Vector2f StatusBar::getSize() const
{
	return _space;
}

bool StatusBar::isResized() const
{
	return _isresized;
}

void StatusBar::resetResized()
{
	_isresized = false;
	return;
}



void StatusBar::updateSpace(float kx, float ky)
{
	update(0.0f);
	setSpace(
		{_text->getGlobalBounds().width*kx,
		_space.y = _text->getGlobalBounds().height*ky}
	);
	return;
}

void StatusBar::updateSpace(sf::Vector2f const &k)
{
	updateSpace(k.x, k.y);
	return;
}



sf::Text const *StatusBar::getText() const
{
	return _text;
}

void StatusBar::setText(sf::Text *newtext)
{
	if(_text == newtext)
		return;
	if(_text)
		delete _text;
	_text = newtext;
	if(_text && _status)
		_text->setString(_status->get());
	if(_align != left)
		_adjustPosition();
	return;
}



clever::ChangingObject<std::string> const *StatusBar::getStatus() const
{
	return _status;
}

void StatusBar::setStatus(
	clever::ChangingObject<std::string> const *newstatus
)
{
	if(_status == newstatus)
		return;
	_status = newstatus;
	if(_text && _status)
		_text->setString(_status->get());
	if(_align != left)
		_adjustPosition();
	return;
}



sf::Vector2f StatusBar::getSpace() const
{
	return _space;
}

void StatusBar::setSpace(sf::Vector2f const &newspace)
{
	_space = newspace;
	_isresized = true;
	if(_align != left)
		_adjustPosition();
	return;
}



StatusBar::Aligning StatusBar::getAligning() const
{
	return _align;
}

void StatusBar::setAligning(StatusBar::Aligning newalign)
{
	_align = newalign;
	_adjustPosition();
	return;
}



void StatusBar::_adjustPosition()
{
	if(_text) {
		switch(_align) {
		case left:
			_text->setPosition({0.0f, 0.0f});
			_text->move(
				-_text->getLocalBounds().left,
				-_text->getLocalBounds().top
			);
			break;
		case center:
			_text->setPosition({
				(_space.x-_text->getGlobalBounds().width)/2,
				(_space.y-_text->getGlobalBounds().height)/2
			});
			_text->move(
				-_text->getLocalBounds().left,
				-_text->getLocalBounds().top
			);
			break;
		case right:
			_text->setPosition({
				_space.x - _text->getGlobalBounds().width,
				_space.y - _text->getGlobalBounds().height
			});
			_text->move(
				-_text->getLocalBounds().left,
				-_text->getLocalBounds().top
			);
			break;
		default:
			throw "Undefined Aligning";
		}
	}
	return;
}



// end.
