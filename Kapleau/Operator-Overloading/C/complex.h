/* complex.h */

#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <string>

struct Complex
{
  Complex(double = 0.0, double = 0.0);

  friend Complex operator+(const Complex &, const Complex &);
  friend Complex operator+(const Complex &, double);
  friend Complex operator+(double, const Complex &);

  friend Complex operator-(const Complex &, const Complex &);
  friend Complex operator-(const Complex &, double);
  friend Complex operator-(double, const Complex &);

  friend Complex operator*(const Complex &, const Complex &);
  friend Complex operator*(const Complex &, double);
  friend Complex operator*(double, const Complex &);

  friend Complex operator/(const Complex &, const Complex &);
  friend Complex operator/(const Complex &, double);
  friend Complex operator/(double, const Complex &);

  friend std::ostream &operator<<(std::ostream &, const Complex &);

  double getReal(void) const;

  double getFake(void) const;
  
private:
  double real;
  double fake;
};

#endif
