#include<iostream>

using namespace std;

class Point
{
public:
	double x, y;

	Point(int n = 0, int m = 0);
	Point(const Point&);
	Point& operator=(const Point&);
	Point operator+(const Point&);
	Point operator-(const Point&);
	Point operator/(int);
	Point right(int);
	Point left(int);
	Point up(int);
	Point down(int);
	bool operator==(const Point&);
	int x_r();
	int y_r();
};

class Shape
{
protected:
	Point _e, _w, _n, _s, _c, _ne, _nw, _se, _sw, _current;
public:
	Point e();
	Point w();
	Point n();
	Point s();
	Point c();
	Point ne();
	Point nw();
	Point se();
	Point sw();
};

class Dot : public Shape
{
public:
	Dot(Point);
};

class Line : public Shape
{
public:
	Line(Point, Point);
};

class Rectangle : public Shape
{
public:
	Rectangle(Point, Point);
};

class DispWindow : public Point, public Shape
{
protected:
	int _x, _y;
	char **map;
public:
	DispWindow(int, int);
	Point& current();
	Point& current(Point);
	void draw(Dot);
	void draw(Line);
	void draw(Rectangle);
	void show();
};