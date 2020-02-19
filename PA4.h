#include"PA4.cpp"
#include<cmath>

Point::Point(int n, int m)
{
	x = n;
	y = m;
}

Point::Point(const Point& p)
{
	x = p.x;
	y = p.y;
}

Point& Point::operator=(const Point& p)
{
	x = p.x;
	y = p.y;

	return *this;
}

Point Point::operator+(const Point& p)
{
	Point temp;

	temp.x = x + p.x;
	temp.y = y + p.y;

	return temp;
}

Point Point::operator-(const Point& p)
{
	Point temp;

	temp.x = x - p.x;
	temp.y = y - p.y;

	return temp;
}

Point Point::operator/(int a)
{
	Point temp;

	temp.x = x / a;
	temp.y = y / a;

	return temp;
}

Point Point::right(int a = 1)
{
	Point temp(x + a, y);

	return temp;
}

Point Point::left(int a = 1)
{
	Point temp(x - a, y);

	return temp;
}

Point Point::up(int a = 1)
{
	Point temp(x, y - a);

	return temp;
}

Point Point::down(int a = 1)
{
	Point temp(x, y + a);

	return temp;
}

bool Point::operator==(const Point& p)
{
	if (x == p.x && y == p.y)
		return true;
	return false;
}

int Point::x_r()
{
	return x;
}

int Point::y_r()
{
	return y;
}

Point Shape::e()
{
	return _e;
}

Point Shape::w()
{
	return _w;
}

Point Shape::n()
{
	return _n;
}

Point Shape::s()
{
	return _s;
}

Point Shape::c()
{
	return _c;
}

Point Shape::ne()
{
	return _ne;
}

Point Shape::nw()
{
	return _nw;
}

Point Shape::se()
{
	return _se;
}

Point Shape::sw()
{
	return _sw;
}

Dot::Dot(Point p)
{
	_e = _w = _n = _s = _c = _ne = _nw = _se = _sw = p;
}

Line::Line(Point p, Point q)
{
	_n = _ne = _nw = p;
	_s = _se = _sw = q;

	_c = (p + q) / 2;
}

Rectangle::Rectangle(Point p, Point q)
{
	_nw = p;
	_se = q;
	_ne.x = _se.x, _ne.y = _nw.y;
	_sw.x = _nw.x, _sw.y = _se.y;
	_c = (p + q) / 2;
	_n.x = _c.x, _n.y = _nw.y;
	_s.x = _c.x, _s.y = _se.y;
	_e.x = _se.x, _e.y = _c.y;
	_w.x = _nw.x, _w.y = _c.y;
}

DispWindow::DispWindow(int n = 0, int m = 0) : _x(n), _y(m)
{
	map = new char*[_y];

	for (int i = 0; i<_y; i++)
		map[i] = new char[_x];

	for (int i = 0; i<_y; i++)
	{
		for (int j = 0; j<_x; j++)
		{
			map[i][j] = ' ';
		}
	}
}

Point& DispWindow::current()
{
	return _current;
}

Point& DispWindow::current(Point p)
{
	_current = p;

	return _current;
}

void DispWindow::draw(Dot d)
{
	if (d.c().x_r() >= _x || d.c().y_r() >= _y)
		return;

	map[d.c().y_r()][d.c().x_r()] = '*';

	_current = d.c();
}

void DispWindow::draw(Line l)
{
	int d_x = l.s().x_r() - l.n().x_r();
	int d_y = l.s().y_r() - l.n().y_r();

	if (d_y % 2 != 0)
		d_y += 1;
	if (d_x % 2 != 0)
		d_x += 1;
	
	if (abs(d_y) == abs(d_x))
	{
		int c = sqrt((d_x*d_x) + (d_y*d_y)) / sqrt(2);

		if (d_x > 0 && d_y > 0)
		{
			Point p = l.s().x > l.n().x ? l.n() : l.s();

			for (int i = 0; i < c + 1; i++)
			{
				if (p.x >= _x || p.y >= _y)
					return;

				map[(int)p.y][(int)p.x] = '*';
				p.x += 1;
				p.y += 1;
			}
			_current.x = p.x - 1;
			_current.y = p.y - 1;
		}
		
		if (d_x < 0 && d_y > 0)
		{
			Point p = l.s().x > l.n().x ? l.s() : l.n();

			for (int i = 0; i < c + 1; i++)
			{
				if (p.x >= _x || p.y >= _y)
					return;

				map[(int)p.y][(int)p.x] = '*';
				p.x -= 1;
				p.y += 1;
			}
			_current.x = p.x + 1;
			_current.y = p.y - 1;
		}

		if (d_x > 0 && d_y < 0)
		{
			Point p = l.s().x > l.n().x ? l.n() : l.s();

			for (int i = 0; i < c + 1; i++)
			{
				if (p.x >= _x || p.y >= _y)
					return;

				map[(int)p.y][(int)p.x] = '*';
				p.x += 1;
				p.y -= 1;
			}
			_current.x = p.x - 1;
			_current.y = p.y + 1;
		}

		if (d_x < 0 && d_y < 0)
		{
			Point p = l.s().x > l.n().x ? l.s() : l.n();

			for (int i = 0; i < c + 1; i++)
			{
				if (p.x >= _x || p.y >= _y)
					return;

				map[(int)p.y][(int)p.x] = '*';
				p.x -= 1;
				p.y -= 1;
			}
			_current.x = p.x + 1;
			_current.y = p.y + 1;
		}
	}
	
	if (d_x == 0 && d_y < 0)
	{
		int c = sqrt((d_x*d_x) + (d_y*d_y));
		
		Point p = l.s().y > l.n().y ? l.s() : l.n();

		for (int i = 0; i < c + 1; i++)
		{
			if (p.x >= _x || p.y >= _y)
				return;

			map[(int)p.y][(int)p.x] = '*';
			p.y -= 1;
		}
		_current.x = p.x;
		_current.y = p.y + 1;
	}

	if (d_x == 0 && d_y > 0)
	{
		int c = sqrt((d_x*d_x) + (d_y*d_y));

		Point p = l.s().y > l.n().y ? l.n() : l.s();

		for (int i = 0; i < c + 1; i++)
		{
			if (p.x >= _x || p.y >= _y)
				return;

			map[(int)p.y][(int)p.x] = '*';
			p.y += 1;
		}
		_current.x = p.x;
		_current.y = p.y - 1;
	}

	if (d_x > 0 && d_y == 0)
	{
		int c = sqrt((d_x*d_x) + (d_y*d_y));

		Point p = l.s().x > l.n().x ? l.n() : l.s();

		for (int i = 0; i < c + 1; i++)
		{
			if (p.x >= _x || p.y >= _y)
				return;

			map[(int)p.y][(int)p.x] = '*';
			p.x += 1;
		}
		_current.x = p.x - 1;
		_current.y = p.y;
	}

	if (d_x < 0 && d_y == 0)
	{
		int c = sqrt((d_x*d_x) + (d_y*d_y));

		Point p = l.s().x > l.n().x ? l.n() : l.s();

		for (int i = 0; i < c + 1; i++)
		{
			if (p.x >= _x || p.y >= _y)
				return;

			map[(int)p.y][(int)p.x] = '*';
			p.x += 1;
		}
		_current.x = p.x - 1;
		_current.y = p.y;
	}

	if (abs(d_x) != abs(d_y))
	{
		if (d_x > 0 && d_y > 0)
		{
			Point p = l.s().x > l.n().x ? l.s() : l.n();
			double d = d_y > d_x ? (double)d_x / (d_y) : (double)(d_y) / d_x;

			for (int i = 0; p.x > l.n().x+1 || p.y >= l.n().y+1; i++)
			{
				if (p.x >= _x || p.y >= _y)
					return;

				
				
				if (d_y > d_x)
				{
					map[(int)p.y][(int)p.x] = '*';
					p.x -= d;
					p.y -= 1;
					map[(int)p.y][(int)(p.x - d)] = '*';
				}


			}
		}

		if (d_x < 0 && d_y > 0)
		{
			Point p = l.s().x > l.n().x ? l.n() : l.s();
			
			double d = abs(d_y) > abs(d_x) ? (double)abs(d_x) / abs(d_y) : (double)abs(d_y) / abs(d_x);

			for (int i = 0; p.x + 1 <= l.n().x || p.y > l.n().y; i++) 
			{
				if (p.x >= _x || p.y >= _y)
					return;

				if (abs(d_y) > abs(d_x))
				{
					map[(int)p.y][(int)(p.x - d + 1)] = '*';
					p.x += d;
					p.y -= 1;
					map[(int)p.y][(int)(p.x + 1)] = '*';
				}
			}
		}
		
		if (d_x > 0 && d_y < 0)
		{
			Point p = l.s().x > l.n().x ? l.n() : l.s();

			double d = abs(d_y) > abs(d_x) ? (double)abs(d_x) / abs(d_y) : (double)abs(d_y) / abs(d_x);

			for (int i = 0;p.x < l.s().x || p.y > l.s().y ; i++)
			{
				if (p.x >= _x || p.y >= _y)
					return;

				if (abs(d_y) > abs(d_x))
				{
					map[(int)p.y][(int)(p.x - d + 1)] = '*';
					p.x += d;
					p.y -= 1;
					map[(int)p.y][(int)(p.x + 1)] = '*';
				}
			}
		}
	}
}

void DispWindow::draw(Rectangle r)
{
	draw(Line(r.nw(), r.ne()));
	draw(Line(r.ne(), r.se()));
	draw(Line(r.nw(), r.sw()));
	draw(Line(r.sw(), r.se()));

	_current = r.se();
}

void DispWindow::show()
{
	for (int i = 0; i<_y; i++)
	{
		for (int j = 0; j<_x; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}