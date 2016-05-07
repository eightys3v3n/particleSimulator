#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "parse.hpp"
#include "structures.hpp"

double radian(double degree) { return degree * 3.14159265358979323846 / 180.0; }
double radians(double degree) { return radian(degree); }
double degree(double radian) { return radian * 180.0 / 3.14159265358979323846; }
double degrees(double radian) { return degree(radian); }

double stdAngle(double x, double y)
{
  double angle;

  angle = degree(atan( y / x ));

  if (x != 0 && y != 0)
  {
    if (x > 0)
    {
      if (y < 0)
        angle += 360;
    }
    else
    {
      if (y > 0)
        angle += 180;
      else
        angle += 180;
    }
  }
  else
  {
    if (y == 0 && x == 0)
      angle = 0;
    else if (x == 0)
    {
      if (y > 0)
        angle = 90;
      else
        angle = 270;
    }
    else
    {
      if (x > 0)
        angle = 0;
      else
        angle = 180;
    }
  }

  return angle;
}

double stdAngle(Coord one, Coord two) { return stdAngle(two.x - one.x, two.y - one.y); }
