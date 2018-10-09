#include "Simple_window.h" 
#include "Graph.h" 
#include "GUI.h"
#include "Window.h"
#include "Point.h"
#include "std_lib_facilities.h"
#include<vector>
#include<string>
#include <iostream>
#include<sstream>
using namespace Graph_lib;
static double k = 0.25;

vector<Rectangle*> vec;
void Diagonal(double a, double b, double l, int n)
{
	if (n == 0) {
		Rectangle * S = new Rectangle(Point(a, b), l, l);
		vec.push_back(S);           //put the rectangles into the vector
	}
	else {
		Diagonal(a, b + 3 * l * k, l*k, n - 1);
		Diagonal(a + l*k, b + 2 * l * k, l*k, n - 1);
		Diagonal(a + 2 * l*k, b + l * k, l*k, n - 1);
		Diagonal(a + 3 * l*k, b, l*k, n - 1);
		Diagonal(a, b, l, 0);
	}
}                                //the recursive function


int main() {
	cout << "Please enter the x scale of the graph: " << endl;
	double a;
	cin >> a;
	cout << "Please enter the y scale of the graph: " << endl;
	double b;
	cin >> b;
	cout << "Please enter the side lengh of the squre: " << endl;
	double l;
	cin >> l;
	cout << "Please enter the order of the graph: " << endl;
	int order;
	cin >> order;
	if (order < 0) {
		order = 0;
	}                                   //if order<=0,print the graph
	Point tl(100, 100);
	Simple_window win(tl, 2*a+l, 2*b+l, "diagonal");  //build the window according to the statistics given
	Diagonal(a, b, l, order);
	for (int i = 0; i < vec.size();i++) {
		win.attach(*vec[i]);
	}                           //draw the rectangles in the vector
	win.wait_for_button();
	for (int i = 0; i < vec.size(); i++) {
		delete vec[i];
	} 
	return 0;
}