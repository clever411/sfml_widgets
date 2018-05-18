#include <exception>
#include "WidgetFactory.hpp"

using namespace clever;



WidgetFactory::WidgetFactory(WidgetFactorySet const *set): _set(set)
{
	if(!_set)
		_set = WidgetFactorySet::getDefault();
}



Button *WidgetFactory::createButton(
	unsigned int decvariant,
	Widget *widget
) const
{
	if(decvariant >= _set->decoratorRectangles.size())
		throw std::out_of_range
			("out of range in decoratorRectangles");
	if(decvariant >= _set->decoratorBorders.size())
		throw std::out_of_range
			("out of range in decoratorBorders");
	return new Button(
		widget,
		new sf::RectangleShape(
			_set->decoratorRectangles[decvariant]
		),
		_set->decoratorBorders[decvariant]
	);
}

Button *WidgetFactory::createButton(
	unsigned int decvariant,
	Widget *widget,
	std::function<void(sf::Mouse::Button)> const &fun
) const
{
	if(decvariant >= _set->decoratorRectangles.size())
		throw std::out_of_range
			("out of range in decoratorRectangles");
	if(decvariant >= _set->decoratorBorders.size())
		throw std::out_of_range
			("out of range in decoratorBorders");

	Button *button = new Button(
		widget,
		new sf::RectangleShape(
			_set->decoratorRectangles[decvariant]
		),
		_set->decoratorBorders[decvariant]
	);
	button->setOnClickFunction(fun);
	
	return button;
}

Layout *WidgetFactory::createLayout(
	unsigned int variant,
	Layout::Orientation orientation,
	std::vector<Widget*> const &elements
) const
{
	if(variant >= _set->layoutBorders.size())
		throw std::out_of_range("out of range in layoutBorders");
	return new Layout(
		orientation, elements, _set->layoutBorders[variant]
	);
}

RectangleDecorator *WidgetFactory::createRectangleDecorator(
	unsigned int variant,
	Widget *widget
) const
{
	if(variant >= _set->decoratorRectangles.size())
		throw std::out_of_range
			("out of range in decoratorRectangles");
	if(variant >= _set->decoratorBorders.size())
		throw std::out_of_range
			("out of range in decoratorBorders");
	return new RectangleDecorator(
		widget,
		new sf::RectangleShape(_set->decoratorRectangles[variant]),
		_set->decoratorBorders[variant]
	);
}


Spacer *WidgetFactory::createSpacer(
	sf::Vector2f const &size
) const
{
	return new Spacer(size);
}

StatusBar *WidgetFactory::createStatusBar(
	unsigned int variant,
	clever::ChangingObject<std::string> const *status
) const
{
	if(variant >= _set->statusbarTexts.size())
		throw std::out_of_range("out of range in statusbarTexts");
	if(status == nullptr) {
		if(variant >= _set->statusbarSpaces.size())
			throw std::out_of_range(
				"out of range in statusbarSpaces"
			);
		return new StatusBar(
			new sf::Text(_set->statusbarTexts[variant]),
			nullptr,
			_set->statusbarSpaces[variant]
		);
	}
	else {
		StatusBar *bar = new StatusBar(
			new sf::Text(_set->statusbarTexts[variant]), status
		);
		bar->updateSpace(1.2f, 1.0f);
		return bar;
	}
}

StatusBar *WidgetFactory::createStatusBar(
	unsigned int variant,
	clever::ChangingObject<std::string> const *status,
	sf::Vector2f const &spaces
) const
{
	if(variant >= _set->statusbarTexts.size())
		throw std::out_of_range("out of range in statusbarTexts");
	return new StatusBar(
		new sf::Text(_set->statusbarTexts[variant]), status, spaces
	);
}



std::pair<Button*, StatusBar*> WidgetFactory::createClickableStatusBar(
	unsigned int decvariant,
	unsigned int barvariant,
	clever::ChangingObject<std::string> const *status
) const
{
	StatusBar *bar = createStatusBar(
		barvariant, status
	);
	Button *button = createButton(
		decvariant, bar
	);

	return std::make_pair(button, bar);
}

std::pair<Button*, StatusBar*> WidgetFactory::createClickableStatusBar(
	unsigned int decvariant,
	unsigned int barvariant,
	clever::ChangingObject<std::string> const *status,
	std::function<void(sf::Mouse::Button)> const &fun
) const
{
	StatusBar *bar = createStatusBar(
		barvariant, status
	);
	Button *button = createButton(
		decvariant, bar, fun
	);

	return std::make_pair(button, bar);
}



std::pair<RectangleDecorator*, Layout*>
WidgetFactory::createDecorativeLayout(
	unsigned int decvariant,
	unsigned int layvariant,
	Layout::Orientation orientation,
	std::vector<Widget*> const &elements
) const
{
	Layout *layout = createLayout(
		layvariant, orientation, elements
	);
	RectangleDecorator *decorator = createRectangleDecorator(
		decvariant, layout
	);
	return std::make_pair(decorator, layout);
}

std::pair<RectangleDecorator*, StatusBar*>
WidgetFactory::createDecorativeStatusBar(
	unsigned int decvariant,
	unsigned int barvariant, 
	clever::ChangingObject<std::string> const *status
) const
{
	StatusBar *bar = createStatusBar(barvariant, status);
	RectangleDecorator *dec = createRectangleDecorator(decvariant, bar);
	return std::make_pair(dec, bar);
}



// end.
