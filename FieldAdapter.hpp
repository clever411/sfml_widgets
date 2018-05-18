#ifndef SFML_FIELD_ADAPTER_HPP
#define SFML_FIELD_ADAPTER_HPP

#include <functional>

#include <clever/Field.hpp>
#include <SFML/Graphics.hpp>

#include "HelpFunctions.hpp"
#include "Widget.hpp"


namespace clever
{



template<typename ValueType, class PrinterType>
class SFMLFieldAdapter: public Widget
{
public:
	typedef ValueType value_type;
	typedef PrinterType printer_type;

	SFMLFieldAdapter(
		Field<value_type> const *field = nullptr,
		sf::Vector2f const &size = {0.0f, 0.0f}
	): _size(size), _field(field) {}

	virtual void update(double time) override;

	virtual void draw(
		sf::RenderTarget &target,
		sf::RenderStates states = sf::RenderStates::Default
	) const override;


	virtual bool isResized() const override;
	virtual void resetResized() override;
	
	virtual sf::Vector2f getSize() const override;
	void setSize(sf::Vector2f const &newsize);
	
	std::pair<unsigned int, unsigned int> cursorOn() const;

	Field<value_type> const *getField() const;
	void setField(Field<value_type> const *newfield);

	printer_type const &getPrinter() const;
	void setPrinter(printer_type const &newprinter);


	float getBordertocell() const;
	void setBordertocell(float newbordertocell);


	bool isDrawBoundsEnable() const;
	void setDrawBoundsEnable(bool enable);

	float getBoundsWidth() const;
	void setBoundsWidth(float newboundswidth);

	sf::Color const &getBoundsColor() const;
	void setBoundsColor(sf::Color const &newboundscolor);


	bool isDrawGridEnable() const;
	void setDrawGridEnable(bool enable);

	float getGridWidth() const;
	void setGridWidth(float newgridwidth);
	
	sf::Color const &getGridColor() const;
	void setGridColor(sf::Color const &newgridcolor);

private:
	void _adjust();

	sf::Vector2f _size;
	Field<value_type> const *_field;
	mutable printer_type _printer;
	sf::Vector2f _boundsoffset;

	float _bordersize = 0, _cellsize = 0;
	float _bordertocell = 0.1;

	sf::RenderTexture _rtexture;
	sf::Sprite _background;

	bool _drawbounds = true;
	float _boundswidth = 5;
	sf::Color _boundscolor = sf::Color::Black;

	bool _drawgrid = true;
	float _gridwidth = 4;
	sf::Color _gridcolor = sf::Color::Black;

	bool _ischanged = false;
	bool _isresized = false;
};

template<typename ValueType, class PrinterType>
void SFMLFieldAdapter<ValueType, PrinterType>::update(double time)
{
	if(_ischanged)
		_adjust();
	return;
}


template<typename ValueType, class PrinterType>
void SFMLFieldAdapter<ValueType, PrinterType>::draw(
	sf::RenderTarget &target, sf::RenderStates states
) const
{
	_printer.setSize({_cellsize, _cellsize});
	_printer.setPosition(
		{_boundsoffset.x+_bordersize,
		_boundsoffset.y+_bordersize}
	);
	states.transform *= sf::Transformable::getTransform();

	target.draw(_background, states);
	for(unsigned int y = 0; y < _field->h; ++y) {
		for(unsigned int x = 0; x < _field->w; ++x) {
			_printer.setValue(_field->d[y*_field->h+x]);
			_printer.draw(target, states);
			_printer.move(_cellsize+2*_bordersize, 0.0);
		}
		_printer.move(
			-int(_field->w)*(_cellsize+2*_bordersize),
			_cellsize+2*_bordersize
		);
	}

	return;
}

template<typename ValueType, class PrinterType>
bool SFMLFieldAdapter<ValueType, PrinterType>::isResized() const
{
	return _isresized;
}
template<typename ValueType, class PrinterType>
void SFMLFieldAdapter<ValueType, PrinterType>::resetResized()
{
	_isresized = false;
	return;
}

template<typename ValueType, class PrinterType>
std::pair<unsigned int, unsigned int>
SFMLFieldAdapter<ValueType, PrinterType>::cursorOn() const
{
	auto mouse = sf::Mouse::getPosition();
	int x = mouse.x/(_cellsize+2*_bordersize);
	int y = mouse.y/(_cellsize+2*_bordersize);

	if(x < 0 || x >= _field->w || y < 0 || y >= _field->h)
		return std::pair<unsigned int, unsigned int>(-1, -1);
	else 
		return std::pair<unsigned int, unsigned int>(
			(unsigned int)(x), (unsigned int)(y)
		);
}



template<typename ValueType, class PrinterType>
sf::Vector2f SFMLFieldAdapter<ValueType, PrinterType>::getSize() const
{
	return _size;
}
template<typename ValueType, class PrinterType>
void SFMLFieldAdapter<ValueType, PrinterType>::setSize(
	sf::Vector2f const &newsize
)
{
	if(_size.x != newsize.x || _size.y != newsize.y) {
		_size = newsize;
		_ischanged = true;
		_isresized = true;
	}
	return;
}

template<typename ValueType, class PrinterType>
Field<typename SFMLFieldAdapter<ValueType, PrinterType>::value_type> const *
SFMLFieldAdapter<ValueType, PrinterType>::getField() const
{
	return _field;
}
template<typename ValueType, class PrinterType>
void SFMLFieldAdapter<ValueType, PrinterType>::setField(
	Field<value_type> const *newfield
)
{
	_field = newfield;
	_ischanged = true;
	return;
}

template<typename ValueType, class PrinterType>
typename SFMLFieldAdapter<ValueType, PrinterType>::printer_type const &
SFMLFieldAdapter<ValueType, PrinterType>::getPrinter() const
{
	return _printer;
}

template<typename ValueType, class PrinterType>
void SFMLFieldAdapter<ValueType, PrinterType>::setPrinter(
	printer_type const &newprinter
)
{
	_printer = newprinter;
}

template<typename ValueType, class PrinterType>
float SFMLFieldAdapter<ValueType, PrinterType>::getBordertocell() const
{
	return _bordertocell;
}
template<typename ValueType, class PrinterType>
void SFMLFieldAdapter<ValueType, PrinterType>::setBordertocell(
	float newbordertocell
)
{
	_bordertocell = newbordertocell;
	_ischanged = true;
	return;
}

template<typename ValueType, class PrinterType>
bool SFMLFieldAdapter<ValueType, PrinterType>::isDrawBoundsEnable() const
{
	return _drawbounds;
}
template<typename ValueType, class PrinterType>
void SFMLFieldAdapter<ValueType, PrinterType>::setDrawBoundsEnable(bool enable)
{
	_drawbounds = enable;
	_ischanged = true;
	return;
}

template<typename ValueType, class PrinterType>
float SFMLFieldAdapter<ValueType, PrinterType>::getBoundsWidth() const
{
	return _boundswidth;
}
template<typename ValueType, class PrinterType>
void SFMLFieldAdapter<ValueType, PrinterType>::setBoundsWidth(
	float newboundswidth
)
{
	_boundswidth = newboundswidth;
	_ischanged = true;
	return;
}

template<typename ValueType, class PrinterType>
sf::Color const &
SFMLFieldAdapter<ValueType, PrinterType>::getBoundsColor() const
{
	return _boundscolor;
}
template<typename ValueType, class PrinterType>
void SFMLFieldAdapter<ValueType, PrinterType>::setBoundsColor(
	sf::Color const &newboundscolor
)
{
	_boundscolor = newboundscolor;
	_ischanged = true;
	return;
}


template<typename ValueType, class PrinterType>
bool SFMLFieldAdapter<ValueType, PrinterType>::isDrawGridEnable() const
{
	return _drawgrid;
}
template<typename ValueType, class PrinterType>
void SFMLFieldAdapter<ValueType, PrinterType>::setDrawGridEnable(bool enable)
{
	_drawgrid = enable;
	_ischanged = true;
	return;
}

template<typename ValueType, class PrinterType>
float SFMLFieldAdapter<ValueType, PrinterType>::getGridWidth() const
{
	return _gridwidth;
}
template<typename ValueType, class PrinterType>
void SFMLFieldAdapter<ValueType, PrinterType>::setGridWidth(float newgridwidth)
{
	_gridwidth = newgridwidth;
	_ischanged = true;
	return;
}


template<typename ValueType, class PrinterType>
sf::Color const &SFMLFieldAdapter<ValueType, PrinterType>::getGridColor() const
{
	return _gridcolor;
}
template<typename ValueType, class PrinterType>
void SFMLFieldAdapter<ValueType, PrinterType>::setGridColor(
	sf::Color const &newgridcolor
)
{
	_gridcolor = newgridcolor;
	_ischanged = true;
	return;
}
	

template<typename ValueType, class PrinterType>
void SFMLFieldAdapter<ValueType, PrinterType>::_adjust()
{
	auto rsize = _size;
	if(_drawbounds) {
		rsize.x -= 2*_boundswidth;
		rsize.y -= 2*_boundswidth;
	}
	float fullcellsize;
	float cwidth = float(rsize.x)/_field->w;
	float cheight = float(rsize.y)/_field->h;
	if(cwidth < cheight) {
		fullcellsize = cwidth;
		_size.y = fullcellsize*_field->h +
			(_drawbounds ? 2*_boundswidth : 0);
		rsize.y = _drawbounds ? _size.y-2*_boundswidth : _size.y;
	}
	else {
		fullcellsize = cheight;
		_size.x = fullcellsize*_field->w +
			(_drawbounds ? 2*_boundswidth : 0);
		rsize.x = _drawbounds ? _size.x-2*_boundswidth : _size.x;
	}
	_isresized = true;

	_cellsize = fullcellsize/(2*_bordertocell+1);
	_bordersize = (fullcellsize-_cellsize)/2;

	_rtexture.create(_size.x, _size.y);
	if(_drawbounds)
		_boundsoffset = {_boundswidth, _boundswidth};
	else
		_boundsoffset = {0, 0};

	if(_drawgrid) {
		sf::RectangleShape rect;
		rect.setFillColor(_gridcolor);

		// Horizontal
		rect.setSize(
			{_field->w*(_cellsize+2*_bordersize), _gridwidth}
		);
		rect.setPosition(
			{_boundsoffset.x, _boundsoffset.y-_gridwidth/2}
		);
		_rtexture.draw(rect);
		for(unsigned short int y = 0; y < _field->h; ++y) {
			rect.move(0.0, _cellsize+2*_bordersize);
			_rtexture.draw(rect);
		}

		// Vertical
		rect.setSize(
			{_gridwidth, _field->h*(_cellsize+2*_bordersize)}
		);
		rect.setPosition(
			{_boundsoffset.x-_gridwidth/2, _boundsoffset.y}
		);
		_rtexture.draw(rect);
		for(unsigned short int x = 0; x < _field->w; ++x) {
			rect.move(_cellsize+2*_bordersize, 0.0);
			_rtexture.draw(rect);
		}
	}

	if(_drawbounds) {
		sf::RectangleShape rect;
		rect.setFillColor(_boundscolor);
		
		// Horizontal
		rect.setSize({_size.x, _boundswidth});
		_rtexture.draw(rect);
		rect.setPosition({0.0f, _size.y-_boundswidth});
		_rtexture.draw(rect);

		// Verical
		rect.setPosition({0.0f, 0.0f});
		rect.setSize({_boundswidth, _size.y});
		_rtexture.draw(rect);
		rect.setPosition({_size.x-_boundswidth, 0.0f});
		_rtexture.draw(rect);

	}

	_rtexture.display();
	_background.setTexture(_rtexture.getTexture(), true);
	_rtexture.setSmooth(true);

	_ischanged = false;

	return;
}



}

#endif // SFML_FIELD_ADAPTER_HPP
