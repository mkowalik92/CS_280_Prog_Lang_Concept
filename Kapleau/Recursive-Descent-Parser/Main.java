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

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    
    public static void main(String[] args)
    {
	File in = new File("input.txt");
	File out = new File("output.txt");

	try (Scanner scan = new Scanner(in);
	     PrintWriter pw = new PrintWriter(new FileWriter(out, true)))
	    {
		while (scan.hasNext())
		{
		    s = scan.next();
		    outputS = s;
		    if ( expre() && (s.length() == 0) )
			{
			    pw.println("The string \"" + outputS + "\" is in the language.");
			}
		    else
			{
			    pw.println("The string \"" + outputS + "\" is not in the language.");
			}
		}
	    }
	catch (IOException e)
	    {
	    e.printStackTrace();
	    System.exit(0);
	    }
	
	/*
	s = args[0];
	
	if ( expre() && (s.length() == 0) )
	    {
		System.out.println("The string \"" + args[0] + "\" is in the language.");
	    }
	else
	    {
		System.out.println("The string \"" + args[0] + "\" is not in the language.");
	    }
	*/
    }

    private static boolean expre()
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

    private static boolean part()
    {
	if ( s.length() == 0 )
	    {
		return false;
	    }
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
	if ( s.charAt(0) == '(' )
	    {
		s = s.substring(1, s.length());
		if ( expre() )
		    {
			if ( s.length() == 0 )
			    {
				return false;
			    }
			if ( s.charAt(0) == ')' )
			    {
				s = s.substring(1, s.length());
				return true;
			    }
			return false;
		    }
		return false;
	    }
	return false;
    }

    private static boolean oper()
    {
	if ( s.length() == 0 )
	    {
		return false;
	    }
	if ( (s.charAt(0) == '*') || (s.charAt(0) == '/') )
	    {
		s = s.substring(1, s.length());
		if ( s.charAt(0) == '*' )
		    {
			s = s.substring(1, s.length());
			return true;
		    }
		if ( s.charAt(0) == '/' )
		    {
			return false;
		    }
		return true;
	    }
	return false;
    }

    private static boolean otherop()
    {
	if ( s.length() == 0 )
	    {
		return false;
	    }
	if ( (s.charAt(0) == '+') || (s.charAt(0) == '-') || (s.charAt(0) == '!') )
	    {
		s = s.substring(1, s.length());
		return true;
	    }
	return false;
    }

    private static boolean id()
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

    private static boolean number()
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

    private static boolean variable()
    {
	if ( s.length() == 0 )
	    {
		return false;
	    }
	//System.out.println("Value and length before variable(): " + s + " | " + s.length());
	if ( (s.charAt(0) == 'a') || (s.charAt(0) == 'b') || (s.charAt(0) == 'c') || (s.charAt(0) == 'd') || (s.charAt(0) == 'e') || (s.charAt(0) == 'f') || (s.charAt(0) == 'g') || (s.charAt(0) == 'h') || (s.charAt(0) == 'i') || (s.charAt(0) == 'j') || (s.charAt(0) == 'k') || (s.charAt(0) == 'l') || (s.charAt(0) == 'm') || (s.charAt(0) == 'n') || (s.charAt(0) == 'o') || (s.charAt(0) == 'p') || (s.charAt(0) == 'q') || (s.charAt(0) == 'r') || (s.charAt(0) == 's') || (s.charAt(0) == 't') || (s.charAt(0) == 'u') || (s.charAt(0) == 'v') || (s.charAt(0) == 'w') || (s.charAt(0) == 'x') || (s.charAt(0) == 'y') || (s.charAt(0) == 'z') )
	    {
		s = s.substring(1, s.length());
		//System.out.println("Value and length after variable(): " + s + " | " + s.length());
		return true;
	    }
	return false;
    }

    private static boolean digit()
    {
	if ( s.length() == 0 )
	    {
		return false;
	    }
	if ( (s.charAt(0) == '0') || (s.charAt(0) == '1') || (s.charAt(0) == '2') || (s.charAt(0) == '3') || (s.charAt(0) == '4') || (s.charAt(0) == '5') || (s.charAt(0) == '6') || (s.charAt(0) == '7') || (s.charAt(0) == '8') || (s.charAt(0) == '9') )
	    {
		s = s.substring(1, s.length());
		return true;
	    }
	return false;
    }
    
    private static String s;
    //Does not change is only referenced when producing output.txt
    private static String outputS;
}
