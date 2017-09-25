#include <iostream>
#include "complex.h"

int main ( int argc, char *argv[] )
{
  Complex a(2.0, 3.0);
  Complex b(4.0, -5.0);
  
  double doubleNum = 2.1;

  std::cout << std::endl;
  
  std::cout << "Complex A: " << a << std::endl;
  std::cout << "Complex B: " << b << std::endl;
  std::cout << "Double: " << doubleNum << std::endl;

  std::cout << std::endl;

  std::cout << "(A)" << " + " << "(B)" << " = " << a + b << std::endl;
  std::cout << "(B)" << " + " << "(" << doubleNum << ")" << " = " << b + doubleNum << std::endl;
  std::cout << "(" << doubleNum << ")" << " + " << "(B)" << " = " << doubleNum + b << std::endl;

  std::cout << std::endl;
  
  std::cout << "(A)" << " - " << "(B)" << " = " << a - b << std::endl;
  std::cout << "(B)" << " - " << "(" << doubleNum << ")" << " = " << b - doubleNum << std::endl;
  std::cout << "(" << doubleNum << ")" << " - " << "(B)" << " = " << doubleNum - b << std::endl;

  std::cout << std::endl;

  std::cout << "(A)" << " * " << "(B)" << " = " << a * b << std::endl;
  std::cout << "(B)" << " * " << "(" << doubleNum << ")" << " = " << b * doubleNum << std::endl;
  std::cout << "(" << doubleNum << ")" << " * " << "(B)" << " = " << doubleNum * b << std::endl;

  std::cout << std::endl;

  std::cout << "(A)" << " / " << "(B)" << " = " << a / b << std::endl;
  std::cout << "(B)" << " / " << "(" << doubleNum << ")" << " = " << b / doubleNum << std::endl;
  std::cout << "(" << doubleNum << ")" << " / " << "(B)" << " = " << doubleNum / b << std::endl;

  std::cout << std::endl;
    
  return 0;
}
