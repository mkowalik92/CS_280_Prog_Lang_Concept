/*
Marek Kowalik
CS 280 - 141
31010270

Recursive Descent Parser

E -> P O P | P
O -> + | - | * | / | **
P -> I | L | UI | UL | (E)
U -> + | - | !
I -> C | CI
C -> a | b | ... | y | z
L -> D | DL
D -> 0 | 1 | ... | 8 | 9
*/

#include <iostream>
#include <string>
#include <fstream>

bool expre(void);
bool oper(void);
bool part(void);
bool otherop(void);
bool id(void);
bool number(void);
bool variable(void);
bool digit(void);

std::string s;
std::string outputStr;

bool expre()
{
  if ( part() )
    {
      if ( otherop() || oper() )
	{
	  if ( part() )
	    {
	      if ( otherop() )
		{
		  if ( expre() )
		    {
		      return true;
		    }
		  return false;
		}
	      return true;
	    }
	  return false;
	}
      return true;
    }
  return false;
}

bool part()
{
  if ( id() )
    {
      return true;
    }
  if ( number() )
    {
      return true;
    }
  if ( otherop() )
    {
      if ( id() )
	{
	  return true;
	}
      if ( number() )
	{
	  return true;
	}
      return false;
    }
  if ( s[0] == '(' )
    {
      s = s.substr(1, s.length() - 1);
      if ( expre() )
	{
	  if ( s.length() == 0 )
	    {
	      return false;
	    }
	  if ( s[0] == ')' )
	    {
	      s = s.substr(1, s.length() - 1);
	      return true;
	    }
	  return false;
	}
      return false;
    }
  return false;
}

bool oper()
{
  if ( (s[0] == '*') || (s[0] == '/') )
    {
      s = s.substr(1, s.length() - 1);
      if ( s[0] == '*' )
	{
	  s = s.substr(1, s.length() - 1);
	  return true;
	}
      if ( s[0] == '/' )
	{
	  return false;
	}
      return true;
    }
  return false;
}

bool otherop()
{
  if ( (s[0] == '+') || (s[0] == '-') || (s[0] == '!') )
    {
      s = s.substr(1, s.length() - 1);
      return true;
    }
  return false;
}

bool id()
{
  if ( variable() )
    {
      if ( id() )
	{
	  return true;
	}
      return true;
    }
  return false;
}

bool number()
{
  if ( digit() )
    {
      if ( number() )
	{
	  return true;
	}
      return true;
    }
  return false;
}

bool variable()
{
  if ( (s[0] == 'a') || (s[0] == 'b') || (s[0] == 'c') || (s[0] == 'd') || (s[0] == 'e') || (s[0] == 'f') || (s[0] == 'g') || (s[0] == 'h') || (s[0] == 'i') || (s[0] == 'j') || (s[0] == 'k') || (s[0] == 'l') || (s[0] == 'm') || (s[0] == 'n') || (s[0] == 'o') || (s[0] == 'p') || (s[0] == 'q') || (s[0] == 'r') || (s[0] == 's') || (s[0] == 't') || (s[0] == 'u') || (s[0] == 'v') || (s[0] == 'w') || (s[0] == 'x') || (s[0] == 'y') || (s[0] == 'z') )
    {
      s = s.substr(1, s.length() - 1);
      return true;
    }
  return false;
}

bool digit()
{
  if ( (s[0] == '0') || (s[0] == '1') || (s[0] == '2') || (s[0] == '3') || (s[0] == '4') || (s[0] == '5') || (s[0] == '6') || (s[0] == '7') || (s[0] == '8') || (s[0] == '9') )
    {
      s = s.substr(1, s.length() - 1);
      return true;
    }
  return false;
}

int main(void)
{
  std::ifstream fin("input.txt");
  std::ofstream fout("output.txt", std::ios::out | std::ios::app);

  while (fin >> s)
    {
      outputStr = s;
      if ( expre() && (s == "") )
	{
	  fout << "The string \"" << outputStr << "\" is in the language." << std::endl;
	  //std::cout << "The string \"" << outputStr << "\" is in the language." << std::endl;
	}
      else
	{
	  fout << "The string \"" << outputStr << "\" is not in the language." << std::endl;
	  //std::cout << "The string \"" << outputStr << "\" is not in the language." << std::endl;
	}
    }
  
  fout.close();
  fin.close();
  
  return 0;
}
