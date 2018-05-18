#include "WidgetFactorySet.hpp"

using namespace clever;
using namespace sf;



WidgetFactorySet::WidgetFactorySet() {}
WidgetFactorySet::~WidgetFactorySet() {}

WidgetFactorySet const *WidgetFactorySet::getDefault()
{
	static WidgetFactorySet set = _initDefault();
	return &set;
}

WidgetFactorySet WidgetFactorySet::_initDefault()
{
	static Font font = _initFont();
	WidgetFactorySet set;
	

	set.layoutBorders.push_back({5, 5});

	RectangleShape rect;
	rect.setFillColor(Color(0xf2, 0x85, 0x00));
	set.decoratorRectangles.push_back(rect);
	set.decoratorBorders.push_back({10, 10});

	rect.setOutlineThickness(0.0f);
	rect.setFillColor(Color(0xea, 0x75, 0x00));
	set.decoratorRectangles.push_back(rect);
	set.decoratorBorders.push_back({10, 10});

	rect.setFillColor(Color(0xb8, 0x5c, 0x00));
	set.decoratorRectangles.push_back(rect);
	set.decoratorBorders.push_back({10, 10});


	Text text;
		text.setString("The Start");
		text.setFont(font);
		text.setCharacterSize(70);
		text.setFillColor(Color::Black);
		text.setOutlineThickness(3);
		text.setOutlineColor(Color::White);
	set.statusbarTexts.push_back(text);
	set.statusbarSpaces.push_back(
		{text.getLocalBounds().width, text.getLocalBounds().height}
	);
		text.setCharacterSize(55);
		text.setOutlineThickness(0);
	set.statusbarTexts.push_back(text);
	set.statusbarSpaces.push_back(
		{text.getLocalBounds().width, text.getLocalBounds().height}
	);
		text.setCharacterSize(40);
		text.setOutlineThickness(0);
	set.statusbarTexts.push_back(text);
	set.statusbarSpaces.push_back(
		{text.getLocalBounds().width, text.getLocalBounds().height}
	);
	

	return set;
}

Font WidgetFactorySet::_initFont()
{
	Font font;
	if(!font.loadFromFile("BittypixMonospace.otf"))
		throw "don't can load font";
	return font;
}



// end.
