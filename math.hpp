#ifndef MATH_
#define MATH_

#include <cmath>
#include <vector>
#include <SFML/System.hpp>
#include "parse.hpp"
#include "structures.hpp"

double radian(double degree);
double radians(double degree);
double degree(double radian);
double degrees(double radian);
double stdAngle(Coord one, Coord two);
double stdAngle(double x, double y);

#endif // MATH_