#include "Line.hpp"

#include "../Utils/Utility.hpp"
#include "Screen.hpp"
#include "Point.hpp"
#include "Circle.hpp"

Line &Line::moveBy(const Vec2 v)
{
  begin += v;
  end += v;
}

Line Line::movedBy(const Vec2 v) const
{
  return Line(begin + v, end + v);
}

// Bresenham's line algorithm: https://ja.wikipedia.org/wiki/ブレゼンハムのアルゴリズム
void Line::draw(const Color color, const int thickness) const
{
  int x0 = static_cast<int>(begin.x + 0.5), y0 = static_cast<int>(begin.y + 0.5),
      x1 = static_cast<int>(end.x + 0.5), y1 = static_cast<int>(end.y + 0.5);

  const Point upperLeft(Min(x0, x1), Min(y0, y1)), lowerRight(Max(x0, x1), Max(y0, y1));
  if (lowerRight.x < 0 || lowerRight.y < 0)
    return;
  if (upperLeft.x > (int)Screen::Width() || upperLeft.y > (int)Screen::Height())
    return;

  const int halfThickness = thickness / 2;

  const bool steep = Math::Abs(y1 - y0) > Math::Abs(x1 - x0);

  if (steep)
  {
    Swap(x0, y0);
    Swap(x1, y1);
  }
  if (x0 > x1)
  {
    Swap(x0, x1);
    Swap(y0, y1);
  }

  const int deltax = x1 - x0, deltay = Math::Abs(y1 - y0);
  int error = deltax / 2;

  const int ystep = (y0 < y1) ? 1 : -1;

  int y = y0;

  for (int x = x0; x <= x1; x++)
  {
    if (steep)
    {
      if (thickness == 1)
        Point(y, x).draw(color);
      else
        Circle(y, x, halfThickness).draw(color);
    }
    else
    {
      if (thickness == 1)
        Point(x, y).draw(color);
      else
        Circle(x, y, halfThickness).draw(color);
    }
    
    error = error - deltay;
    if (error < 0)
    {
      y += ystep;
      error += deltax;
    }
  }
}
