#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <fstream>
#include <istream>

//Argument flags - If 0 the argument was not used
int vflag = 0;
int statsflag = 0;
int sumflag = 0;

//String definitions for arguments
std::string tokprintvar = "-v";
std::string statprintvar = "-stats";
std::string sumprintvar = "-sum";

//Regex definitions for identifying ids
std::regex idstart("[a-zA-Z]");
std::regex idend("[^a-zA-Z0-9]");
std::regex iddefined("([a-zA-Z]{1}[a-zA-Z0-9]*)");

//Regex definitions for identifying ints/floats
std::regex numberstart("[0-9|\\.]");
std::regex numberend("[^0-9|\\.]");
std::regex numberdefined("-?[0-9]+\\.?[0-9]+");
std::regex intdefined("-?[0-9]+");
std::regex floatdefined("-?[0-9]+\\.[0-9]+");

//Regex definitions for identifying strings
std::regex stringstart("\"");
std::regex stringend("\"");
std::regex stringdefined("\".*\"");

//Regex definitions for identifying set/print tokens
//Still need to add
std::regex printtoken("print");
std::regex settoken("set");

std::vector<std::string> idtokens,inttokens,floattokens,stringtokens,printtokens,settokens,plustokens,minustokens,startokens,commatokens,lbrtokens,rbrtokens,lsqtokens,rsqtokens,lparentokens,rparentokens,sctokens;

//Vector containing non-duplicate and sorted id tokens
std::vector<std::string> nondupsortedidtokens;

//If this is 0 then there are no tokens.
int uniquetokencount = 0;

//Array containing tokentype/tokencount
std::string possiblelargestarray[17][17];

//Vector containing the sorted largest token counts
std::vector<std::string> sortedlargesttokens;

int lineCount = 0;
int fileCount = 0;
std::string fileName;

bool checkArg ( std::string argv )
{
  if ( (argv == tokprintvar) || (argv == statprintvar) || (argv == sumprintvar) )
    {
      return true;
    }
  else
    {
      std::cout << "Invalid argument " << argv << std::endl;
      return false;
    }
}

bool checkFile ( std::string fileName )
{
  std::ifstream myfile (fileName);
  if ( !myfile.is_open() )
    {
      std::cout << "Could not open " << fileName << std::endl;
      return false;
    }
  else
    {
      myfile.close();
      return true;
    }
}

void sortidtokens ()
{
  for ( int i = 0; i<idtokens.size(); i++ )
    {
      if ( i == 0 )
	{
	  nondupsortedidtokens.push_back(idtokens[i]);
	}
      else
	{
	  if ( std::find(nondupsortedidtokens.begin(),nondupsortedidtokens.end(),idtokens[i]) != nondupsortedidtokens.end() )
	    {
	      continue;
	    }
	  else
	    {
	      nondupsortedidtokens.push_back(idtokens[i]);
	    }
	}
    }
  std::sort(nondupsortedidtokens.begin(),nondupsortedidtokens.end());
}
int tokensum ()
{
  int sum = idtokens.size() + stringtokens.size() + inttokens.size() + floattokens.size() + printtokens.size() + settokens.size() + plustokens.size() + minustokens.size() + startokens.size() + commatokens.size() + lbrtokens.size() + rbrtokens.size() + lsqtokens.size() + rsqtokens.size() +lparentokens.size() + rparentokens.size() + sctokens.size();
  return sum;
}

void howmanyuniquetokens ()
{
  if ( idtokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( stringtokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( inttokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( floattokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( printtokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( settokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( plustokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( minustokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( startokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( commatokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( lbrtokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( rbrtokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( lsqtokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( rsqtokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( lparentokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( rparentokens.size() > 0 )
    {
      uniquetokencount++;
    }
  if ( sctokens.size() > 0 )
    {
      uniquetokencount++;
    }
}

void mostfrequenttokens ()
{
  //ID tokens
  possiblelargestarray[0][0] = "ID";
  possiblelargestarray[0][1] = std::to_string(idtokens.size());
  //STRING tokens
  possiblelargestarray[1][0] = "STRING";
  possiblelargestarray[1][1] = std::to_string(stringtokens.size());
  //ICONST tokens
  possiblelargestarray[2][0] = "ICONST";
  possiblelargestarray[2][1] = std::to_string(inttokens.size());
  //FCONST tokens
  possiblelargestarray[3][0] = "FCONST";
  possiblelargestarray[3][1] = std::to_string(floattokens.size());
  //PRINT tokens
  possiblelargestarray[4][0] = "PRINT";
  possiblelargestarray[4][1] = std::to_string(printtokens.size());
  //SET tokens
  possiblelargestarray[5][0] = "SET";
  possiblelargestarray[5][1] = std::to_string(settokens.size());
  //PLUS tokens
  possiblelargestarray[6][0] = "PLUS";
  possiblelargestarray[6][1] = std::to_string(plustokens.size());
  //MINUS tokens
  possiblelargestarray[7][0] = "MINUS";
  possiblelargestarray[7][1] = std::to_string(minustokens.size());
  //STAR tokens
  possiblelargestarray[8][0] = "STAR";
  possiblelargestarray[8][1] = std::to_string(startokens.size());
  //COMMA tokens
  possiblelargestarray[9][0] = "COMMA";
  possiblelargestarray[9][1] = std::to_string(commatokens.size());
  //LBR tokens
  possiblelargestarray[10][0] = "LBR";
  possiblelargestarray[10][1] = std::to_string(lbrtokens.size());
  //RBR tokens
  possiblelargestarray[11][0] = "RBR";
  possiblelargestarray[11][1] = std::to_string(rbrtokens.size());
  //LSQ tokens
  possiblelargestarray[12][0] = "LSQ";
  possiblelargestarray[12][1] = std::to_string(lsqtokens.size());
  //RSQ tokens
  possiblelargestarray[13][0] = "RSQ";
  possiblelargestarray[13][1] = std::to_string(rsqtokens.size());
  //LPAREN tokens
  possiblelargestarray[14][0] = "LPAREN";
  possiblelargestarray[14][1] = std::to_string(lparentokens.size());
  //RPAREN tokens
  possiblelargestarray[15][0] = "RPAREN";
  possiblelargestarray[15][1] = std::to_string(rparentokens.size());
  //SC tokens
  possiblelargestarray[16][0] = "SC";
  possiblelargestarray[16][1] = std::to_string(sctokens.size());

  //Sort array in descending order according to token vector size
  std::string temptokenstring;
  std::string temptokensizestring;
  int firstint;
  int nextint;
  for ( int i = 0; i<17; i++ )
    {
      for ( int j = i + 1; j<17; ++j )
	{
	  firstint=stoi(possiblelargestarray[i][1]);
	  nextint=stoi(possiblelargestarray[j][1]);
	  if ( firstint < nextint )
	    {
	      temptokenstring=possiblelargestarray[i][0];
	      temptokensizestring=possiblelargestarray[i][1];
	      possiblelargestarray[i][0]=possiblelargestarray[j][0];
	      possiblelargestarray[i][1]=possiblelargestarray[j][1];
	      possiblelargestarray[j][0]=temptokenstring;
	      possiblelargestarray[j][1]=temptokensizestring;
	    }
	}
    }
}

void sortlargesttokens ()
{
  for ( int i = 0; i<17; i++ )
    {
      sortedlargesttokens.push_back(possiblelargestarray[i][0]);
      if ( possiblelargestarray[i][1] != possiblelargestarray[i+1][1] )
	{
	  break;
	}
    }
}

void parseFile ( std::istream& source )
{
  std::ifstream myfile(fileName);
  std::string line;
  while ( getline(source,line) )
    {
      lineCount++;
      if ( line[0] == '#' )
	{
	  continue;
	}
      else
	{
	  std::string potentialid;
	  std::string potentialnumber;
	  std::string potentialstring;
	  for ( int i = 0; i<line.length(); i++ )
	    {
	      std::string firstchar(1,line[i]);
	      //If the character pulled from the line is a letter
	      if ( std::regex_match(firstchar,idstart) )
		{
		  potentialid+=firstchar;
		  for ( int j = i + 1; j<line.length(); j++ )
		    {
		      std::string nextchar(1,line[j]);
		      if ( std::regex_match(nextchar,idend) )
			{
			  if ( std::regex_match(potentialid,printtoken) )
			    {
			      printtokens.push_back(potentialid);
			    }
			  else if ( std::regex_match(potentialid,settoken) )
			    {
			      settokens.push_back(potentialid);
			    }
			  else if ( std::regex_match(potentialid,iddefined) )
			    {
			      if ( vflag > 0 )
				{
				  std::cout << "ID (" << potentialid << ")\n";
				}
			      idtokens.push_back(potentialid);
			    }
			  else
			    {
			      std::cout << "Error on line " << lineCount << " (" << potentialid << ")" << std::endl;
			      exit(EXIT_FAILURE);
			    }
			  potentialid.clear();
			  break;
			}
		      else
			{
			  i++;
			  potentialid+=nextchar;
			  if ( j == (line.length() - 1) )
			    {
			      if ( std::regex_match(potentialid,printtoken) )
				{
				  printtokens.push_back(potentialid);
				}
			      else if ( std::regex_match(potentialid,printtoken) )
				{
				  settokens.push_back(potentialid);
				}
			      else if ( std::regex_match(potentialid,iddefined) )
				{
				  if ( vflag > 0 )
				    {
				      std::cout << "ID (" << potentialid << ")\n";
				    }
				  idtokens.push_back(potentialid);
				}
			      else
				{
				  std::cout << "Error on line " << lineCount << " (" << potentialid << ")" << std::endl;
				  exit(EXIT_FAILURE);
				}
			    }
			}
		    }
		}
	      //If the character pulled from the line is a digit
	      if ( std::regex_match(firstchar,numberstart) )
		{
		  if ( (line.length() > 1) && (i != 0) )
		    {
		      if ( line[i-1] == '-' )
			{
			  potentialnumber+=line[i-1];
			}
		    }
		  potentialnumber+=firstchar;
		  for ( int m = i + 1; m<line.length(); m++ )
		    {
		      std::string nextchar(1,line[m]);
		      if ( std::regex_match(nextchar,numberend) )
			{
			  //std::cout << "Potential Number: " << potentialnumber << std::endl;
			  if ( std::regex_match(potentialnumber,intdefined) )
			    {
			      if ( vflag > 0 )
				{
				  std::cout << "ICONST (" << potentialnumber << ")\n";
				}
			      inttokens.push_back(potentialnumber);
			    }
			  else if ( std::regex_match(potentialnumber,floatdefined) )
			    {
			      if ( vflag > 0 )
				{
				  std::cout << "FCONST (" << potentialnumber << ")\n";
				}
			      floattokens.push_back(potentialnumber);
			    }
			  else
			    {
			      std::cout << "Error on line " << lineCount << " (" << potentialnumber[0] << ")" << std::endl;
			      exit(EXIT_FAILURE);
			    }
			  if (m == (line.length() - 2) )
			    {
			      potentialnumber.clear();
			      continue;
			    }
			  potentialnumber.clear();
			  break;
			}
		      else
			{
			  i++;
			  potentialnumber+=nextchar;
			  if ( m == (line.length() - 1) )
			    {
			      //std::cout << "Potential Number: " << potentialnumber << std::endl;
			      if ( std::regex_match(potentialnumber,intdefined) )
				{
				  if ( vflag > 0 )
				    {
				      std::cout << "ICONST (" << potentialnumber << ")\n";
				    }
				  inttokens.push_back(potentialnumber);
				}
			      else if ( std::regex_match(potentialnumber,floatdefined) )
				{
				  if ( vflag > 0 )
				    {
				      std::cout << "FCONST (" << potentialnumber << ")\n";
				    }
				  floattokens.push_back(potentialnumber);
				}
			      else
				{
				  std::cout << "Error on line " << lineCount << " (" << potentialnumber[0] << ")" << std::endl;
				  exit(EXIT_FAILURE);
				}
			    }
			}
		    }
		  
		}
	      //If the character pulled from the line is a quote
	      if ( std::regex_match(firstchar,stringstart) )
		{
		  potentialstring+=firstchar;
		  for ( int n = i + 1; n<line.length(); n++ )
		    {
		      std::string nextchar(1,line[n]);
		      if ( std::regex_match(nextchar,stringend) )
			{
			  potentialstring+=nextchar;
			  i++;
			  if ( std::regex_match(potentialstring,stringdefined) )
			    {
			      if ( vflag > 0 )
				{
				  std::cout << "STRING (" << potentialstring << ")\n";
				}
			      stringtokens.push_back(potentialstring);
			    }
			  else
			    {
			      std::cout << "Error on line " << lineCount << " (" << potentialstring << ")" << std::endl;
			      exit(EXIT_FAILURE);
			    }
			  potentialstring.clear();
			  break;
			}
		      else
			{
			  i++;
			  potentialstring+=nextchar;
			  if ( n == (line.length() - 1) )
			    {
			      if ( std::regex_match(potentialstring,stringdefined) )
				{
				  if ( vflag > 0 )
				    {
				      std::cout << "STRING (" << potentialstring << ")\n";
				    }
				  stringtokens.push_back(potentialstring);
				}
			      else
				{
				  std::cout << "Error on line " << lineCount << " (" << potentialstring << ")" << std::endl;
				  exit(EXIT_FAILURE);
				}
			    }
			}
		    }
		}
	      if ( firstchar == "+" )
		{
		  if ( vflag > 0 )
		    {
		      std::cout << "PLUS\n";
		    }
		  plustokens.push_back(firstchar);
		}
	      if ( firstchar == "-" )
		{
		  if ( vflag > 0 )
		    {
		      std::cout << "MINUS\n";
		    }
		  minustokens.push_back(firstchar);
		}
	      if ( firstchar == "*" )
		{
		  if ( vflag > 0 )
		    {
		      std::cout << "STAR\n";
		    }
		  startokens.push_back(firstchar);
		}
	      if ( firstchar == "," )
		{
		  if ( vflag > 0 )
		    {
		      std::cout << "COMMA\n";
		    }
		  commatokens.push_back(firstchar);
		}
	      if ( firstchar == "{" )
		{
		  if ( vflag > 0 )
		    {
		      std::cout << "LBR\n";
		    }
		  lbrtokens.push_back(firstchar);
		}
	      if ( firstchar == "}" )
		{
		  if ( vflag > 0 )
		    {
		      std::cout << "RBR\n";
		    }
		  rbrtokens.push_back(firstchar);
		}
	      if ( firstchar == "[" )
		{
		  if ( vflag > 0 )
		    {
		      std::cout << "LSQ\n";
		    }
		  lsqtokens.push_back(firstchar);
		}
	      if ( firstchar == "]" )
		{
		  if ( vflag > 0 )
		    {
		      std::cout << "RSQ\n";
		    }
		  rsqtokens.push_back(firstchar);
		}
	      if ( firstchar == "(" )
		{
		  if ( vflag > 0 )
		    {
		      std::cout << "LPAREN\n";
		    }
		  lparentokens.push_back(firstchar);
		}
	      if ( firstchar == ")" )
		{
		  if ( vflag > 0 )
		    {
		      std::cout << "RPAREN\n";
		    }
		  rparentokens.push_back(firstchar);
		}
	      if ( firstchar == ";" )
		{
		  if ( vflag > 0 )
		    {
		      std::cout << "SC\n";
		    }
		  sctokens.push_back(firstchar);
		}
	      if ( firstchar == "#" )
		{
		  break;
		}
	    }
	}
    }
}

int main( int argc, char *argv[] )
{
  //parseFile(argv[1]);
  for ( int g = 1; g<argc; g++ )
    {
      if ( argv[g][0] == '-' )
	{
	  if ( !checkArg(argv[g]) )
	    {
	      return 0;
	    }
	  else
	    {
	      if ( argv[g] == tokprintvar )
		{
		  vflag++;
		}
	      if ( argv[g] == statprintvar )
		{
		  statsflag++;
		}
	      if ( argv[g] == sumprintvar )
		{
		  sumflag++;
		}
	    }
	}
      else
	{
	  if ( !checkFile(argv[g]) )
	    {
	      return 0;
	    }
	  else
	    {
	      if ( fileCount > 0 )
		{
		  std::cout << "Too many file names\n";
		  return 0;
		}
	      else
		{
		  fileName = argv[g];
		  fileCount++;
		}
	    }
	}
    }

  if ( fileCount > 0 )
    {
      std::ifstream ifile(fileName);
      parseFile(ifile);
    }
  else
    {
      parseFile(std::cin);
    }
  
  //Argument (-stats/-sum) Output Triggers
  if ( statsflag > 0 )
    {
      std::cout << "Total IDs: " << idtokens.size() << std::endl;
      if ( idtokens.size() > 0 )
	{
	  std::cout << "List of IDs: ";
	  if ( idtokens.size() < 2 )
	    {
	      std::cout << idtokens[0];
	    }
	  else
	    {
	      sortidtokens();
	      for ( int x = 0; x<nondupsortedidtokens.size(); x++ )
		{
		  if ( x == (nondupsortedidtokens.size() - 1) )
		    {
		      std::cout << nondupsortedidtokens[x];
		    }
		  else
		    {
		      std::cout << nondupsortedidtokens[x] << ", ";
		    }
		}
	    }
	  std::cout << std::endl;
	}
    }
  if ( sumflag > 0 )
    {
      std::cout << "Total lines: " << lineCount << std::endl;
      std::cout << "Total tokens: " << tokensum() << std::endl;
      if ( tokensum() > 0 )
	{
	  //Print most frequently used tokens
	  std::cout << "Most frequently used tokens: ";
	  mostfrequenttokens();
	  howmanyuniquetokens();
	  if ( uniquetokencount < 2 )
	    {
	      std::cout << possiblelargestarray[0][0] << std::endl;
	    }
	  //Else sort array into vector
	  else
	    {
	      sortlargesttokens();
	      std::sort(sortedlargesttokens.begin(),sortedlargesttokens.end());
	      for ( int z = (sortedlargesttokens.size() - 1); z>=0; z-- )
		{
		  //std::cout << z << std::endl;
		  std::cout << sortedlargesttokens[z];
		  if ( z > 0 )
		    {
		      std::cout << ", ";
		    }
		}
	      std::cout << std::endl;
	    }
	}
    }
  //std::cout << "Total Lines: " << lineCount << std::endl;
  //std::cout << "Total IDs: " << idtokens.size() << std::endl;
  //std::cout << "Total INTs: " << inttokens.size() << std::endl;
  //std::cout << "Total FLOATs: " << floattokens.size() << std::endl;
  //std::cout << "Total PRINTs: " << printtokens.size() << std::endl;
  //std::cout << "Total SETs: " << settokens.size() << std::endl;
  //std::cout << "Total PLUSs: " << plustokens.size() << std::endl;
  //std::cout << "Total MINUSs: " << minustokens.size() << std::endl;
  //std::cout << "Total STARs: " << startokens.size() << std::endl;
  //std::cout << "Total COMMAs: " << commatokens.size() << std::endl;
  //std::cout << "Total LBRs: " << lbrtokens.size() << std::endl;
  //std::cout << "Total RBRs: " << rbrtokens.size() << std::endl;
  //std::cout << "Total LSQs: " << lsqtokens.size() << std::endl;
  //std::cout << "Total RSQs: " << rsqtokens.size() << std::endl;
  //std::cout << "Total LPARENs: " << lparentokens.size() << std::endl;
  //std::cout << "Total RPARENs: " << rparentokens.size() << std::endl;
  //std::cout << "Total SCs: " << sctokens.size() << std::endl;
  return 0;
}
