#include <bits/stdc++.h>
using namespace std;

// haversine formula
double gcDist(double pLa, double pLo, double qLa, double qLo, double r) {
  pLa *= M_PI/180; pLo *= M_PI/180;           // degree to radian
  qLa *= M_PI/180; qLo *= M_PI/180;
  return r * acos(cos(pLa)*cos(pLo)*cos(qLa)*cos(qLo) +
         cos(pLa)*sin(pLo)*cos(qLa)*sin(qLo) + sin(pLa)*sin(qLa));
}


/*
Simpson's rule for integration:

integral(a, b, fx) = delta_x/3 * (f(x0) + 4f(x1) + 2f(x2) + ... + 4 f(xn-1) + f(xn)) deltax = (b-a)/n, xi = a + i*deltax
how to calculate it (C program for the formula)

Check kattis/bottles for code using it
https://www.bragitoff.com/2017/08/simpsons-13-rule-c-program/


error: https://www.cuemath.com/simpsons-rule-formula/
M * (b - a)^5 / (180 * n^4)
*/
