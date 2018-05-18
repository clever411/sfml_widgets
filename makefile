all: Widget.o Layout.o RectangleDecorator.o Button.o StatusBar.o Spacer.o \
	WidgetFactory.o WidgetFactorySet.o
	ar rvs libclever-sfmlwidgets.a Widget.o Layout.o \
		RectangleDecorator.o Button.o StatusBar.o Spacer.o \
		WidgetFactory.o WidgetFactorySet.o

Widget.o: Widget.cpp
	g++ -o Widget.o -c Widget.cpp

Layout.o: Layout.cpp
	g++ -o Layout.o -c Layout.cpp

RectangleDecorator.o: RectangleDecorator.cpp
	g++ -o RectangleDecorator.o -c RectangleDecorator.cpp

Button.o: Button.cpp
	g++ -o Button.o -c Button.cpp

StatusBar.o: StatusBar.cpp
	g++ -o StatusBar.o -c StatusBar.cpp

Spacer.o: Spacer.cpp
	g++ -o Spacer.o -c Spacer.cpp
	
WidgetFactory.o: WidgetFactory.cpp
	g++ -o WidgetFactory.o -c WidgetFactory.cpp

WidgetFactorySet.o: WidgetFactorySet.cpp
	g++ -o WidgetFactorySet.o -c WidgetFactory.cpp

clear:
	rm *.o
