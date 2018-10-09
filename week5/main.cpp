#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1
#include "Simple_window.h" // get access to our window library
#include "Graph.h" // get access to our graphics library facilities
#include "GUI.h"
#include "Window.h"
#include "Point.h"
int main()
{
	using namespace Graph_lib; // our graphics facilities are in Graph_lib
	Point tl{ 100,100 }; // to become top left corner of window
	Simple_window win{ tl,600,400,"Canvas" }; // make a simple window
	Circle c1(Point(140, 150), 70);
	c1.set_style(Line_style(Line_style::solid,10));  
	c1.set_color(Color::blue);
	win.attach(c1); //the first circle
	Circle c2(Point(300, 150), 70);
	c2.set_style(Line_style(Line_style::solid, 10));
	c2.set_color(Color::black);
	win.attach(c2);//the second circle
	Circle c3(Point(460, 150), 70);
	c3.set_style(Line_style(Line_style::solid, 10));
	c3.set_color(Color::red);
	win.attach(c3);//the third circle
	Circle c4(Point(220, 220), 70);
	c4.set_style(Line_style(Line_style::solid, 10));
	c4.set_color(Color::yellow);
	win.attach(c4);//the forth circle
	Circle c5(Point(380, 220), 70);
	c5.set_style(Line_style(Line_style::solid, 10));
	c5.set_color(Color::dark_green);
	win.attach(c5);//the fifth circlr
	win.wait_for_button(); // give control to the display engine
}